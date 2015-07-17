#ifndef PHYSICS_VECTOR3D_HPP_
#define PHYSICS_VECTOR3D_HPP_
/*
 * Basic 3-dimensional vector and related operations.
 *
 * Author: Nathan Hemmings
 *
 * Date created: 07/06/2015
 *
 */
 #include "physics/precision.hpp"
 
 namespace physics {
	class Vector3D {
	public:
		real x;
		real y;
		real z;
		
		/** Default constructor creates a zero vector. */
		Vector3D() : x(0), y(0), z(0) {}
		
		/** Creates a vector with the given components. */
		Vector3D(const real x, const real y, const real z) : x(x), y(y), z(z) {}
		
		/** Inverts the components of this vector */
		void invert() {
			x = -x;
			y = -y;
			z = -z;
		}
		
		/** Gets the magnitude of this vector. */
		real magnitude() const {
			return real_sqrt(x*x + y*y + z*z);
		}
		
		/** Gets the squared magnitude of this vector. */
		real squareMagnitude() const {
			return x*x + y*y + z*z;
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
			z *= value;
		}
		
		/** Returns a copy of this vector scaled by the given value. */
		Vector3D operator*(const real value) const {
			return Vector3D(x*value, y*value, z*value);
		}
		
		/** Adds the given vector to this. */
		void operator+=(const Vector3D& v) {
			x += v.x;
			y += v.y;
			z += v.z;
		}
		
		/** Returns the value of the given vector added to this. */
		Vector3D operator+(const Vector3D& v) const {
			return Vector3D(x+v.x, y+v.y, z+v.z);
		}
		
		/** Subtracts the given vector from this */
		void operator-=(const Vector3D& v) {
			x-= v.x;
			y -= v.y;
			z -= v.z;
		}
		
		/** Returns the value of the given vector subtracted from this. */
		Vector3D operator-(const Vector3D& v) const {
			return Vector3D(x-v.x, y-v.y, z-v.z);
		}
		
		/** 
		 *	Scales the given vector by the given amount and adds the result
		 *	to this vector. 
		 */
		void addScaledVector(const Vector3D& v, real scale) {
			x += v.x * scale;
			y += v.y * scale;
			z += v.z * scale;
		}
		 
		/**
		 *	Calculates and returns a component-wise product of this vector with the
		 *	given vector.
		 */
		Vector3D componentProduct(const Vector3D& v) const {
			return Vector3D(x * v.x, y * v.y, z * v.z);
		}
		
		/**
		 *	Sets this vector to the result of performing a component-wise multiplication
		 *	of this vector and the given vector.
		 */
		void componentProductUpdate(const Vector3D& v) {
			x *= v.x;
			y *= v.y;
			z *= v.z;
		}
		
		/** Calculates and returns the scalar product of this vector with the given vector. */
		real scalarProduct(const Vector3D& v) const {
			return x * v.x + y * v.y + z * v.z;
		}
		
		/** Calculates and returns the scalar product of this vector with the given vector. */
		real operator*(const Vector3D& v) const {
			return x * v.x + y * v.y + z * v.z;
		}
		
		/** Calculates and returns the vector product of this vector with the given vector. */
		Vector3D vectorProduct(const Vector3D& v) const {
			return Vector3D(y*v.z - z*v.y,
									z*v.x - x*v.z,
									x*v.y - y*v.x);
		}
		
		/** Updates this vector to be the vector product of its current value and the given vector. */
		void operator%=(const Vector3D& v) {
			*this = vectorProduct(v);
		}
		
		/** Calculates and returns the vector product of this vector with the given vector. */
		Vector3D operator%(const Vector3D& v) const {
			return Vector3D(y*v.z - z*v.y,
									z*v.x - x*v.z,
									x*v.y - y*v.x);
		}
		
		void makeOrthonormalBasis(Vector3D *a, Vector3D *b, Vector3D *c) {
			a->normalize();
			(*c) = (*a) % (*b);
			if (c.squareMagnitude() == 0.0) return;		// or throw an error (means a and b are parallel)
			c->normalize();
			(*b) = (*c) % (*a);
		}
	 };	// Vector3D
 }	// namespace physics
 
 #endif // PHYSICS_VECTOR3D_HPP_