//
// Created by Amila Perera on 12/03/2019.
//
#include "util/streams/io_stream.hh"

namespace eel {
namespace util {

IOStream& IOStream::Print(const char *fmt, ...) {
  return *this;
}

}
}
