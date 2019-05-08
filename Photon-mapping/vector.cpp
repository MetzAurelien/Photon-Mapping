#include <vector.h>

namespace photonmapping
{

    template<typename T>
    Vector3D<T>::Vector3D() : x_(0), y_(0), z_(0), norm_(0), squared_norm_(0)
    {
    }

    template<typename T>
    Vector3D<T>::Vector3D(T x, T y, T z) : x_(x), y_(y), z_(z)
    {
        update();
    }

    template<typename T>
    Vector3D<T>::Vector3D(const Vector3D<T>& v)
        : x_(v.x_), y_(v.y_), z_(v.z_), norm_(v.norm_), squared_norm_(v.squared_norm_)
    {
    }

    template<typename T>
    Vector3D<T>& Vector3D<T>::operator=(const Vector3D& v)
    {
        x_ = v.x_;
        y_ = v.y_;
        z_ = v.z_;
        norm_ = v.norm_;
        squared_norm_ = v.squared_norm_;
        return *this;
    }

    template<typename T>
    T Vector3D<T>::get_x() const { return x_; }
    template<typename T>
    T Vector3D<T>::get_y() const { return y_; }
    template<typename T>
    T Vector3D<T>::get_z() const { return z_; }

    template<typename T>
    T Vector3D<T>::get_norm() const { return norm_; }
    template<typename T>
    T Vector3D<T>::get_squared_norm() const { return squared_norm_; }

    template<typename T>
    Vector3D<T> Vector3D<T>::operator-() const
    {
        return Vector3D<T>(-x_, -y_, -z_, norm_, squared_norm_);
    }
    template<typename T>
    Vector3D<T> Vector3D<T>::get_normalized_coppy() const
    {
        return Vector3D<T>(x_ / norm_, y_ / norm_, z_ / norm_, 1, 1);
    }

    template<typename T>
    void Vector3D<T>::set(T x, T y, T z)
    {
        x_ = x;
        y_ = y;
        z_ = z;
        update();
    }
    template<typename T>
    void Vector3D<T>::set_x(T x) { set(x, y_, z_); }
    template<typename T>
    void Vector3D<T>::set_y(T y) { set(x_, y, z_); }
    template<typename T>
    void Vector3D<T>::set_z(T z) { set(x_, y_, z); }

    template<typename T>
    Vector3D<T>& Vector3D<T>::operator+=(const Vector3D& v)
    {
        set(x_ + v.x_, y_ + v.y_, z_ + v.z_);
        return *this;
    }
    template<typename T>
    Vector3D<T>& Vector3D<T>::operator-=(const Vector3D& v)
    {
        set(x_ - v.x_, y_ - v.y_, z_ - v.z_);
        return *this;
    }
    template<typename T>
    Vector3D<T>& Vector3D<T>::operator*=(T scalar_value)
    {
        set(x_ * scalar_value, y_ * scalar_value, z_ * scalar_value);
        return *this;
    }
    template<typename T>
    Vector3D<T>& Vector3D<T>::operator/=(T scalar_value)
    {
        set(x_ / scalar_value, y_ / scalar_value, z_ / scalar_value);
        return *this;
    }

    template<typename T>
    void Vector3D<T>::normalize() { *this /= norm_; }

    template<typename T>
    Vector3D<T> Vector3D<T>::projection(const Vector3D<T>& left_vector, const Vector3D<T>& right_vector)
    {
        return Vector3D<T>(left_vector * ((left_vector * right_vector) / (left_vector * left_vector)));
    }
    template<typename T>
    Vector3D<T> Vector3D<T>::distance_ratio_to_point(
        const Vector3D<T>& origin, const Vector3D<T>& direction, T distance
    )
    {
        return (origin + (direction * distance));
    }

    template<typename T>
    Vector3D<T>::Vector3D(T x, T y, T z, T norm, T squared_norm)
        : x_(x), y_(y), z_(z), norm_(norm), squared_norm_(squared_norm)
    {
    }

    template<typename T>
    void Vector3D<T>::update()
    {
        squared_norm_ = (x_ * x_) + (y_ * y_) + (z_ * z_);
        norm_ = std::sqrt(squared_norm_);
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Vector3D<T>& v)
    {
        os << std::fixed << "(";
        os << v.get_x() << ", ";
        os << v.get_y() << ", ";
        os << v.get_z() << ")";
        return os;
    }

    template<typename T>
    Vector3D<T> operator+(const Vector3D<T>& left_vector, const Vector3D<T>& right_vector)
    {
        return Vector3D<T>(
            left_vector.get_x() + right_vector.get_x(),
            left_vector.get_y() + right_vector.get_y(),
            left_vector.get_z() + right_vector.get_z()
            );
    }
    template<typename T>
    Vector3D<T> operator-(const Vector3D<T>& left_vector, const Vector3D<T>& right_vector)
    {
        return Vector3D<T>(
            left_vector.get_x() - right_vector.get_x(),
            left_vector.get_y() - right_vector.get_y(),
            left_vector.get_z() - right_vector.get_z()
            );
    }
    template<typename T>
    T operator*(const Vector3D<T>& left_vector, const Vector3D<T>& right_vector)
    {
        return (
            (left_vector.get_x() * right_vector.get_x()) +
            (left_vector.get_y() * right_vector.get_y()) +
            (left_vector.get_z() * right_vector.get_z())
            );
    }
    template<typename T>
    Vector3D<T> operator^(const Vector3D<T>& left_vector, const Vector3D<T>& right_vector)
    {
        return Vector3D<T>(
            left_vector.get_z() * right_vector.get_y() - (left_vector.get_y() * right_vector.get_z()),
            left_vector.get_x() * right_vector.get_z() - (left_vector.get_z() * right_vector.get_x()),
            left_vector.get_y() * right_vector.get_x() - (left_vector.get_x() * right_vector.get_y())
            );
    }
    template<typename T>
    Vector3D<T> operator*(const Vector3D<T>& v, T scalar_value)
    {
        return Vector3D<T>(v.get_x() * scalar_value, v.get_y() * scalar_value, v.get_z() * scalar_value);
    }
    template<typename T>
    Vector3D<T> operator*(T scalar_value, const Vector3D<T>& v)
    {
        return Vector3D<T>(v.get_x() * scalar_value, v.get_y() * scalar_value, v.get_z() * scalar_value);
    }
    template<typename T>
    Vector3D<T> operator/(const Vector3D<T>& v, T scalar_value)
    {
        return Vector3D<T>(v.get_x() / scalar_value, v.get_y() / scalar_value, v.get_z() / scalar_value);
    }
    template<typename T>
    Vector3D<T> operator/(T scalar_value, const Vector3D<T>& v)
    {
        return Vector3D<T>(v.get_x() / scalar_value, v.get_y() / scalar_value, v.get_z() / scalar_value);
    }

    template Vector3D<double>;
    template Vector3D<float>;

} // namespace photonmapping