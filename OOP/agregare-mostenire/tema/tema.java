class A {
    public void foo() {

    }

    public C bar(C c) {
        return new C(); // irelevant continutul
    }
}

class B extends A {
    // suprascrieti si supraincarcati metodele foo() si bar() in toate modurile corecte si incorecte posibile
    public void foo() {
        System.out.println("void");
    }
    public void foo(int x) {
        System.out.println(x);
    }
    public C bar() {
        C ceva;
        return ceva;
    }
    public C bar(C ceva, int x) {
        System.out.println("In " + ceva + "se afla" + x + "elemente");
        return ceva;
    }

}

class C {

}

class D extends C {

}
