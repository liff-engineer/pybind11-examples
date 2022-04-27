from TestModule import IActor,Actor,Test


class MyIActor(IActor):
    def __init__(self):
        super().__init__()
        print("MyIActor")

    def Launch(self):
        print("MyIActor::Launch")


#class MyActor(Actor):
#    def __init__(self):
#        super().__init__()
#        print("MyActor")
    
#    def Alloc(self):
#        print("MyActor::Alloc")
#        return MyIActor()

o1 = MyIActor()
Test(o1)
print("UseO1")
Test(o1)
o2 = MyIActor()
Test(o2)
Test(o1)
#obj = MyActor()
#obj.What()

