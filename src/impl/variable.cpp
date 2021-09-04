#include <hdrs/variable.h>

#include <tuple>

bool TVariable::operator<(const TVariable &obj) const {
    return std::tie(number, state) < std::tie(obj.number, obj.state);
}

bool TVariable::operator==(const TVariable &obj) const {
    return std::tie(number, state) == std::tie(obj.number, obj.state);
}

std::istream& operator>>(std::istream &is, TVariable &obj) {
    std::streamoff pos = (is >> std::ws).tellg();
    if (is.eof()) {
        is.setstate(std::istream::failbit | std::istream::eofbit);
        return is;
    }
    obj = TVariable();
    int32_t symbol = is.get();
    switch (symbol) {
    case '!':
        symbol = is.get();
        if (symbol != VARIABLE) {
            is.seekg(pos);
            is.setstate(std::istream::failbit);
            return is;
        }
        obj.state = EState::Negative;
    case VARIABLE:
        if (isspace(is.peek()) || !(is >> obj.number)) {
            is.seekg(pos);
            is.setstate(std::istream::failbit);
        }
        if (obj.state == EState::Empty) {
            obj.state = EState::Positive;
        }
        break;
    case '1':
        obj.state = EState::Positive;
    case '0':
        obj.number = 0;
        break;
    default:
        is.seekg(pos);
        is.setstate(std::istream::failbit);
    }
    return is;
}

std::ostream& operator<<(std::ostream &os, const TVariable &obj) {
    if (obj.number) {
        if (obj.state == EState::Negative) {
            os << '!';
        }
        return os << VARIABLE << obj.number;
    }
    return os << static_cast<int32_t>(obj.state);
}
