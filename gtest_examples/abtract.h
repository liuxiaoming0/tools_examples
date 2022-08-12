namespace stl {
class AbtractShow {
  public:
    AbtractShow() = default;
    virtual ~AbtractShow() = default;

    virtual void SetData(const int& v) = 0;
    virtual int GetData() final {return value_;}
  protected:
    int value_;
};


class Impl1 : public AbtractShow {
  public:
    void SetData(const int& v)override {
      value_ = v;
      // std::cout << "value=" << value_ <<std::endl;
    }
};

class Impl2 : public AbtractShow {
  public:
    void SetData(const int& v)override {
      value_ = 2*v;
      // std::cout << "v=" << v <<std::endl;
    }
};

class Impl3 : public AbtractShow {
  public:
    Impl3(int a, int b) : a_(a), b_(b){}
    void SetData(const int& v)override {
      value_ = a_ + b_ + v;
      // std::cout << "a=" << a_ << ",b=" << b_ << ",v=" << v <<std::endl;
    }
  private:
    int a_;
    int b_;
};

}