#Banking System
#By Ainedembe Denis - 2024-M132-23999

import time    # Used for timestamping logs
import pickle  # Used for saving/loading account data

# Base Class ------------------------------------------------------------------------------------
class Account:
    def __init__(self, acc_no, name, currency="UGX", balance=0.0):
        # Initialize account details
        self.acc_no = acc_no
        self.name = name
        self.currency = currency
        self.balance = balance

    def deposit(self, amount):
        # Add money to account balance
        self.balance += amount
        Logger.log("DEPOSIT", self.acc_no, amount)
        print(f"Deposited {amount} {self.currency}. New balance: {self.balance} {self.currency}")

    def withdraw(self, amount):
        # Withdraw money if sufficient balance exists
        if amount <= self.balance:
            self.balance -= amount
            Logger.log("WITHDRAW", self.acc_no, amount)
            print(f"Withdrew {amount} {self.currency}. Remaining balance: {self.balance} {self.currency}")
        else:
            print("Insufficient funds!")

    def display_balance(self):
        # Display current account balance
        Logger.log("CHECK-BAL", self.acc_no, self.balance)
        print(f"Account {self.acc_no} ({self.name}) Balance: {self.balance} {self.currency}")


# -------------------- SAVINGS ACCOUNT --------------------
class SavingsAccount(Account):
    def withdraw(self, amount):
        # Override: Savings account does not allow overdraft
        if amount > self.balance:
            print("Cannot withdraw: insufficient funds in Savings Account.")
        else:
            super().withdraw(amount)  # Call parent method


# Current Account ----------------------------------------------------------------------------
class CurrentAccount(Account):
    def __init__(self, acc_no, name, currency="UGX", balance=0.0, overdraft_limit=500.0):
        # Initialize base attributes + overdraft feature
        super().__init__(acc_no, name, currency, balance)
        self.overdraft_limit = overdraft_limit

    def withdraw(self, amount):
        # Override: allows overdraft up to a limit
        if amount <= self.balance + self.overdraft_limit:
            self.balance -= amount
            Logger.log("CURRENT_WITHDRAW", self.acc_no, amount)
            print(f"Current account withdrawal of {amount} {self.currency}. Remaining balance: {self.balance} {self.currency}")
        else:
            print("Withdrawal exceeds overdraft limit!")


# Audit Logging Class -------------------------------------------------------------------------
class Logger:
    logfile = "audit_log.txt"  # File to store audit logs

    @staticmethod
    def log(action, acc_no, amount):
        # Record system activities with timestamp
        with open(Logger.logfile, "a") as log:
            timestamp = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
            log.write(f"{timestamp} | ACTION:{action} | Account:{acc_no} | Amount:{amount}\n")


# User Authentication ------------------------------------------------------------------------
class UserSystem:
    # Predefined users and roles simulating login system
    USERS = {"Teller1": "Teller123", "Sysadmin": "admin123"}
    ROLES = {"Teller1": "TELLER", "Sysadmin": "ADMIN"}

    @staticmethod
    def login():
        # Simple login mechanism
        username = input("Username: ")
        password = input("Password: ")
        if username in UserSystem.USERS and UserSystem.USERS[username] == password:
            role = UserSystem.ROLES[username]
            Logger.log("LOGIN-SUCCESS", 0, 0)
            print(f"{role} login successful.")
            return role
        else:
            Logger.log("LOGIN-FAILED", 0, 0)
            print("Invalid credentials!")
            return None


# File Persistence ----------------------------------------------------------------
DATA_FILE = "accounts.dat"  # File to store account data

def save_accounts(accounts):
    """Save all accounts to accounts.dat using pickle."""
    with open(DATA_FILE, "wb") as f:
        pickle.dump(accounts, f)

def load_accounts():
    """Load accounts from accounts.dat. Returns empty dict if file doesn't exist."""
    try:
        with open(DATA_FILE, "rb") as f:
            return pickle.load(f)
    except FileNotFoundError:
        return {}


# Main System ----------------------------------------------------------------------
def main():
    accounts = load_accounts()  # Load saved accounts from file
    role = UserSystem.login()
    if not role:
        return

    while True:
        print("\nBANKING SYSTEM___________________")

        # Display menu based on user role
        if role == "TELLER":
            print("1. Create Account")
            print("2. Deposit")
            print("3. Withdraw")
            print("4. Check Balance")
            print("5. Exit")
        else:  # ADMIN
            print("1. View Logs")
            print("2. Exit")

        choice = input("Enter choice: ")

        if role == "TELLER":
            if choice == "1":
                # Create new account
                acc_no = int(input("Enter account number: "))
                name = input("Enter account holder name: ")
                currency = input("Currency (UGX/USD): ")
                balance = float(input("Initial deposit: "))
                acc_type = input("Type (savings/current): ").lower()

                # Instantiate appropriate class
                if acc_type == "savings":
                    accounts[acc_no] = SavingsAccount(acc_no, name, currency, balance)
                else:
                    accounts[acc_no] = CurrentAccount(acc_no, name, currency, balance)

                Logger.log("CREATED-ACCOUNT", acc_no, balance)
                save_accounts(accounts)  # Persist to file
                print("Account created successfully.")

            elif choice == "2":
                # Deposit money
                acc_no = int(input("Enter account number: "))
                amount = float(input("Deposit amount: "))
                accounts[acc_no].deposit(amount)
                save_accounts(accounts)  # Persist to file

            elif choice == "3":
                # Withdraw money
                acc_no = int(input("Enter account number: "))
                amount = float(input("Withdraw amount: "))
                accounts[acc_no].withdraw(amount)
                save_accounts(accounts)  # Persist to file

            elif choice == "4":
                # Display account balance
                acc_no = int(input("Enter account number: "))
                accounts[acc_no].display_balance()

            elif choice == "5":
                Logger.log("LOGOUT", 0, 0)
                print("Exiting...")
                break

        else:  # ADMIN
            if choice == "1":
                # View audit logs
                with open(Logger.logfile, "r") as log:
                    print("\nAudit Logs__________")
                    print(log.read())

            elif choice == "2":
                Logger.log("LOGOUT", 0, 0)
                print("Exiting...")
                break


# Entry point
if __name__ == "__main__":
    main()