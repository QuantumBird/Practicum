#include "basic_mat.hpp"

namespace SPACE_NAME {
// namespace begin
template<bool A, bool B>
struct bool_and {
  static const bool value = A && B;
};

template<bool A, bool B>
struct bool_or {
  static const bool value = A || B;
};

template<bool A>
struct bool_not {
  static const bool value = !A;
};

template<bool A, bool B>
struct bool_eql {
  static const bool value = (A == B);
};



// namespace end
}
///////////// Inference the TPmat mult //////////////////



