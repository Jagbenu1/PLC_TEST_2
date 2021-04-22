x=1
y=3
z=5
def sub1():
    a=7
    y=9
    z=11
    def sub2():
        global x
        a=13
        x=15
        w=17
        def sub3():
            nonlocal a
            a=19
            b=21
            z=23
            def sub4():
                nonlocal b
                y=43
                b=61
                w=23
