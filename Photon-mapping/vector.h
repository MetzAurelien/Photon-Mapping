#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>

namespace photonmapping
{

    template<typename T>
    class Vector3D
    {
    public:

        using size_type = std::size_t;

        Vector3D();
        Vector3D(T x, T y, T z);

        Vector3D(const Vector3D&);
        Vector3D& operator=(const Vector3D&);

        T get_x() const;
        T get_y() const;
        T get_z() const;

        T get_norm() const;
        T get_squared_norm() const;

        Vector3D operator-() const;
        Vector3D get_normalized_coppy() const;

        void set(T x, T y, T z);
        void set_x(T x);
        void set_y(T y);
        void set_z(T z);

        Vector3D& operator+=(const Vector3D&);
        Vector3D& operator-=(const Vector3D&);
        Vector3D& operator*=(T scalar_value);
        Vector3D& operator/=(T scalar_value);

        void normalize();

        static Vector3D projection(const Vector3D&, const Vector3D&);
        static Vector3D distance_ratio_to_point(const Vector3D& origin, const Vector3D& direction, T distance);

    private:

        Vector3D(T x, T y, T z, T norm, T norm_squared);

        void update();

        T norm_;
        T squared_norm_;
        T x_;
        T y_;
        T z_;
    };

    template<typename T>
    using Point3D = Vector3D<T>;

    template<typename T>
    std::ostream& operator<<(std::ostream&, const Vector3D<T>&);

    template<typename T>
    Vector3D<T> operator+(const Vector3D<T>&, const Vector3D<T>&);

    template<typename T>
    Vector3D<T> operator-(const Vector3D<T>&, const Vector3D<T>&);

    template<typename T>
    T operator*(const Vector3D<T>&, const Vector3D<T>&);

    template<typename T>
    Vector3D<T> operator^(const Vector3D<T>&, const Vector3D<T>&);

    template<typename T>
    Vector3D<T> operator*(const Vector3D<T>&, T scalar_value);

    template<typename T>
    Vector3D<T> operator*(T scalar_value, const Vector3D<T>&);

    template<typename T>
    Vector3D<T> operator/(const Vector3D<T>, T scalar_value);

    template<typename T>
    Vector3D<T> operator/(T scalar_value, const Vector3D<T>);

} // namespace photonmapping

#endif // VECTOR_H_