#include <iostream>
#include <climits>
#include <stdexcept>

namespace pluzhnik
{
  struct MaxCounter
  {
  public:
    MaxCounter() :
      max_len_pos_(0),
      len_pos_(0),
      temp_val_(0),
      is_first_(true)
    {}

    void operator()(int val)
    {
      if (val == 0)
      {
        if (len_pos_ > max_len_pos_)
        {
          max_len_pos_ = len_pos_;
        }
        return;
      }

      if (is_first_)
      {
        len_pos_ = 1;
        is_first_ = false;
      }
      else if (val >= temp_val_)
      {
        if (len_pos_ < INT_MAX)
        {
          ++len_pos_;
        }
        else
        {
          throw std::overflow_error("Error: overflow len_pos");
        }
      }
      else
      {
        if (len_pos_ > max_len_pos_)
        {
          max_len_pos_ = len_pos_;
        }
        len_pos_ = 1;
      }

      temp_val_ = val;
    }

    int operator()() const
    {
      return max_len_pos_;
    }

  private:
    int max_len_pos_;
    int len_pos_;
    int temp_val_;
    bool is_first_;
  };
}

int main()
{
  try
  {
    pluzhnik::MaxCounter counter;
    int val = 0;

    while (true)
    {
      if (!(std::cin >> val))
      {
        throw std::invalid_argument("Error: invalid input format");
      }

      counter(val);

      if (val == 0)
      {
        break;
      }
    }

    std::cout << counter() << "\n";
    return 0;
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
