import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

portfolio = {}


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    update_portfolio()

    stocks_value = 0
    for i in list(portfolio.keys()):
        stocks_value += lookup(i)["price"] * portfolio[i]

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    grand_total = cash + stocks_value

    return render_template("index.html", cash=cash, grand_total=grand_total, portfolio=portfolio, lookup=lookup, usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        symbol_lookup = lookup(request.form.get("symbol"))

        if symbol_lookup == None:
            return apology("Symbol not found", 400)

        symbol = symbol_lookup["symbol"]
        price = float(symbol_lookup["price"])
        price_usd = usd(price)
        shares = request.form.get("shares")
        if shares.isdigit():
            shares = int(shares)
        else:
            return apology("Enter a valid number of shares", 400)

        if shares < 1:
            return apology("Enter a valid number of shares", 400)

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        if cash < (price * shares):
            return apology("You are too poor.", 400)
        cash -= (price * shares)

        db.execute("INSERT INTO purchases (user_id, time, symbol, number_of_shares, price, type) VALUES (?, (SELECT datetime()), ?, ?, ?, 'buy')", session["user_id"], symbol, shares, price)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    historia = db.execute("SELECT * FROM purchases WHERE user_id = ? UNION ALL SELECT * FROM sales WHERE user_id = ? ORDER BY time DESC", session["user_id"], session["user_id"])
    return render_template("history.html", history=historia, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        look_up_symbol = lookup(request.form.get("symbol"))
        if look_up_symbol == None:
            return apology("Symbol not found", 400)
        return render_template("quoted.html", symbol=look_up_symbol["symbol"], price=usd(look_up_symbol["price"]))
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        #Check if username already exists
        username = db.execute("SELECT username FROM users WHERE username = ?", request.form.get("username"))
        for i in username:
            if request.form.get("username") == i["username"]:
                return apology("username already exists", 400)


        if request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))
        return redirect("/")
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol_lookup = lookup(request.form.get("symbol"))

        if symbol_lookup == None:
            return apology("Symbol not found", 400)

        symbol = symbol_lookup["symbol"]
        price = float(symbol_lookup["price"])
        price_usd = usd(price)
        shares = request.form.get("shares")
        if shares.isdigit():
            shares = int(shares)
        else:
            return apology("Enter a valid number of shares", 400)

        if shares < 1:
            return apology("Enter a valid number of shares", 400)

        purchased_shares = db.execute("SELECT SUM(number_of_shares) FROM purchases WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)[0]["SUM(number_of_shares)"]
        if purchased_shares is None:
            purchased_shares = 0

        sold_shares = db.execute("SELECT SUM(number_of_shares) FROM sales WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)[0]["SUM(number_of_shares)"]
        if sold_shares is None:
            sold_shares = 0

        if shares > purchased_shares - sold_shares:
            return apology("Not enough shares", 400)

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        cash += (price * shares)

        db.execute("INSERT INTO sales (user_id, time, symbol, number_of_shares, price, type) VALUES (?, (SELECT datetime()), ?, ?, ?, 'sell')", session["user_id"], symbol, shares, price)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
        return redirect("/")
    update_portfolio()
    return render_template("sell.html", portfolio=portfolio)

def update_portfolio():
    purchased_shares = db.execute("SELECT * FROM purchases WHERE user_id = ?", session["user_id"])
    sold_shares = db.execute("SELECT * FROM sales WHERE user_id = ?", session["user_id"])
    portfolio.clear()
    for s in purchased_shares:
        if not portfolio.get(s["symbol"]):
            portfolio.update({s["symbol"]:s["number_of_shares"]})
        else:
            portfolio.update({s["symbol"]:s["number_of_shares"] + portfolio[s["symbol"]]})

    for s in sold_shares:
        portfolio.update({s["symbol"]:(portfolio[s["symbol"]] - s["number_of_shares"])})

    for i in list(portfolio.keys()):
        if portfolio[i] == 0:
            del portfolio[i]