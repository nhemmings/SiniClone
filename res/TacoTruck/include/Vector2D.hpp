#ifndef PHYSICS_VECTOR2D_HPP_
#define PHYSICS_VECTOR2D_HPP_
/*
 * Basic 2-dimensional vector and related operations.
 *
 * Author: Nathan Hemmings
 *
 * Date created: 07/01/2015
 *
 */
 #include <cmath>
 #include "precision.hpp"

 namespace tacoTruck {
	class Vector2D {
	public:
		real x;
		real y;

		/** Default constructor creates a zero vector. */
		Vector2D() : x(0), y(0) {}

		/** Creates a vector with the given components. */
		Vector2D(const real x, const real y) : x(x), y(y) {}

		/** Inverts the components of this vector */
		void invert() {
			x = -x;
			y = -y;
		}

		void clear() {
            x = y = 0;
		}

		/** Gets the magnitude of this vector. */
		real magnitude() const {
			return std::sqrt(x*x + y*y);
		}

		/** Gets the squared magnitude of this vector. */
		real squareMagnitude() const {
			return x*x + y*y;
		}

		/** Turns a non-zero vector into a vector of unit length. */
		void normalize() {
			real mag = magnitude();
			if ( mag < 0 ) {
				(*this) *= ((real)1)/mag;
			}
		}

		/** Multiplies this vector by the given scalar */
		void operator*=(const real value) {
			x *= value;
			y *= value;
		}

		/** Returns a copy of this vector scaled by the given value. */
		Vector2D operator*(const real value) const {
			return Vector2D(x*value, y*value);
		}

		/** Adds the given vector to this. */
		void operator+=(const Vector2D& v) {
			x += v.x;
			y += v.y;
		}

		/** Returns the value of the given vector added to this. */
		Vector2D operator+(const Vector2D& v) const {
			return Vector2D(x+v.x, y+v.y);
		}

		/** Subtracts the given vector from this */
		void operator-=(const Vector2D& v) {
			x-= v.x;
			y -= v.y;
		}

		/** Returns the value of the given vector subtracted from this. */
		Vector2D operator-(const Vector2D& v) const {
			return Vector2D(x-v.x, y-v.y);
		}

		/**
		 *	Scales the given vector by the given amount and adds the result
		 *	to this vector.
		 */
		void addScaledVector(const Vector2D& v, real scale) {
			x += v.x * scale;
			y += v.y * scale;
		}

		/**
		 *	Calculates and returns a component-wise product of this vector with the
		 *	given vector.
		 */
		Vector2D componentProduct(const Vector2D& v) const {
			return Vector2D(x * v.x, y * v.y);
		}

		/**
		 *	Sets this vector to the result of performing a component-wise multiplication
		 *	of this vector and the given vector.
		 */
		void componentProductUpdate(const Vector2D& v) {
			x *= v.x;
			y *= v.y;
		}

		/** Calculates and returns the scalar product of this vector with the given vector. */
		real scalarProduct(const Vector2D& v) const {
			return x * v.x + y * v.y;
		}

		/** Calculates and returns the scalar product of this vector with the given vector. */
		real operator*(const Vector2D& v) const {
			return x * v.x + y * v.y;
		}

		/** Returns a vector perpendicular to the given vector (with the same magnitude). */
		Vector2D perpendicular(const Vector2D& v) const {
			return Vector2D(-v.y, v.x);
		}
	 };	// Vector2D
 }	// namespace tacoTruck

 #endif // PHYSICS_VECTOR2D_HPP_
