#ifndef streambuf_h
#define streambug_h

#include <streambuf>
#include "window_base.h"

namespace ui {

class streambuf : public std::streambuf {
public: 

    streambuf(window_base& window)
    :   window_(window)
    {
        // set buffer to empty
        setg(getbuf_, getbuf_, getbuf_);
    }

protected:

    int sync() override { window_.refresh(); return 0; }

    int_type overflow(int_type ch = traits_type::eof()) override { 

        if (ch != traits_type::eof())
            window_.putc(ch); 

        return ch;
    }

    std::streamsize xsputn(const char* s, std::streamsize n) override {

        for (unsigned i = 0; i < n; i++)
            overflow(s[i]);

        window_.refresh();

        return n;
    }

    int_type underflow() override {

        if (gptr() < egptr())
            return traits_type::to_int_type(*gptr());

        // read one char in blocking fashion if buffer is empty
        getbuf_[0] = static_cast<char>(window_.getc());

        // try to fill more into the buffer
        window_.set_nodelay(true);
        int c, i;
        for (i = 1; (c = window_.getc()) != ERR && i < sizeof(getbuf_); i++) 
            getbuf_[i] = static_cast<char>(c);

        // turn off nodelay, set pointers and return first char
        window_.set_nodelay(false);
        setg(getbuf_, getbuf_, getbuf_ + i); 
        return *getbuf_;
    }


private:
    window_base& window_;
    char getbuf_[10];
};

} // ui namespace

#endif