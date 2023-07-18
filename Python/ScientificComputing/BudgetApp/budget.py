class Category:
    def __init__(self, cat) -> None:
        self.ledger = []
        self.funds = 0
        self.cat = cat
        
    def deposit(self, amount, description = ""):
        self.ledger.append({"amount":amount, "description":description})
        self.funds += amount
        
    def withdraw(self, amount, description = ""): 
        if self.check_funds(amount):
            self.ledger.append({"amount":-amount, "description":description})
            self.funds -= amount
            return True
        else:
            return False
        
    def get_balance(self):
        return self.funds
    
    def transfer(self, amount, bud):
        if self.check_funds(amount):
            self.withdraw(amount, f"Transfer to {bud.cat}")
            bud.deposit(amount,f"Transfer from {self.cat}")
            return True
        else:
            return False
    
    def check_funds(self, amount):
        sub = self.funds - amount
        if (sub >= 0):
            return True
        else:
            return False
        
    def __str__(self) -> str:
        resume =  f"{self.cat}".center(30,"*")
        for element in self.ledger:
            resume+= "\n"+ "{0:<23}{1:>7.2f}".format(str(element["description"])[:23],(element["amount"]))
        resume += "\n" + f"Total: {self.funds}"
        return resume