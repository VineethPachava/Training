

class A {
 public:
  virtual void f1();
  virtual void f2();
  virtual void f3();
};
class B:public A {
 public:
  virtual void f1();
  virtual void f2();
  virtual void f4();
  virtual void f5(); 
};

class C:public B {
 public:
  virtual void f1();
  virtual void f4();
  virtual void f6(); 
};

int main(){
    
}