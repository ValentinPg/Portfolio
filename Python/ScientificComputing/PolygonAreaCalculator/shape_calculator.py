class Rectangle:
    
    def __init__(self,width,height) -> None:
        self.width = int(width)
        self.height = int(height)
    
    def __str__(self) -> str:
        return f"Rectangle(width={self.width}, height={self.height})"
    
    def set_width(self,width):
        self.width = int(width)
        
    def set_height(self,height):
        self.height = int(height)
        
    def get_area(self):
        return (self.width*self.height)
    
    def get_perimeter(self):
        return (2 * self.width + 2 * self.height)
    
    def get_diagonal(self):
        return ((self.width ** 2 + self.height ** 2) ** .5)
    
    def get_picture(self):
        if ((self.width>50) or (self.height>50)):
            return "Too big for picture."
        
        string = ""
        for line in range(self.height):
            for _ in range(self.width):
                string+= "*"
            string+= "\n"
        return string
    
    def get_amount_inside(self, shape):
        timesWidth = int(self.width / shape.width)
        timesHeight = int(self.height / shape.height)
        return timesHeight*timesWidth
    

class Square(Rectangle):
    
    def __init__(self, length) -> None:
        self.width = int(length)
        self.height = int(length)
        
    def __str__(self) -> str:
        return f"Square(side={self.width})"
    
    def set_side(self,length):
        self.width = int(length)
        self.height = int(length)
        
    def set_width(self,length):
        self.width = int(length)
        self.height = int(length)
        
    def set_height(self,length):
        self.width = int(length)
        self.height = int(length)
            