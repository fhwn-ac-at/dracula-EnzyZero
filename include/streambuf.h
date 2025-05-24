#ifndef streambuf_h
#define streambuf_h

#include <streambuf>
#include "window_base.h"

namespace ui {

class streambuf : public std::streambuf {
public: 

    streambuf(window_base& window)
    :   window_(window)
    {}

    ~streambuf() override = default;

protected:

    int sync() override { window_.refresh(); return 0; }

    int_type overflow(int_type ch = traits_type::eof()) override;

    int_type underflow() override { return traits_type::to_int_type(window_.getc()); }

    int_type uflow() override { return underflow(); }

private:
    window_base& window_;
};

} // ui namespace 


inline std::streambuf::int_type ui::streambuf::overflow(int_type ch) { 

    if (ch != traits_type::eof())
        window_.putc(ch); 

    return ch;
}

#endif