#ifndef LIST_STRONG_TYPES_H
#define LIST_STRONG_TYPES_H

template <typename T, typename P>
class Type {
    const T obj;
public:
    explicit Type(const T&& o): obj{o} {};
    inline const T &get() const {
        return obj;
    };

    bool operator==(const Type &rhs) const {
        return obj == rhs.obj;
    }

    bool operator!=(const Type &rhs) const {
        return !(rhs == *this);
    }

    Type<T, P> operator+(const Type<T, P> &other) const {
        return Type<T, P>{obj+other.obj};
    };
};

#endif //LIST_STRONG_TYPES_H
