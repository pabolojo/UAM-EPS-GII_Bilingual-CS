class Salutation():
    def sayHello(self):
        print("Hello World %s" % self.name)

    def __init__(self, name):
        self.name = name


salutation = Salutation("Pablo")
salutation.sayHello()