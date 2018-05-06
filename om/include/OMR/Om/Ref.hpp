#if !defined(OMR_OM_MEMBERREF_HPP_)
#define OMR_OM_MEMBERREF_HPP_

#include <type_traits>

namespace OMR
{
namespace Om
{
/// A pointer to managed memory. It is GC-Unsafe. This is a very simple
/// pointer-wrapper.
template <typename T>
class Ref
{
public:
	using ElementType = std::remove_extent<T>;

	using DifferenceType = std::ptrdiff_t;

	template <typename U>
	using Rebind = Ref<U>;

	using ConstType = Rebind<const T>;

	constexpr Ref() : value(nullptr) {}

	constexpr Ref(std::nullptr_t) : value(nullptr) {}

	template <typename U>
	constexpr Ref(U* other) : value(reinterpret_cast<T*>(other))
	{
	}

	template <typename U>
	constexpr Ref(const Ref<U>& other);

	/// Access member from Ref.
	constexpr auto operator-> () const -> T*;

	/// Dereference the ref.
	constexpr auto operator*() const -> T&;

	constexpr auto toAddress() const -> void*;

	inline auto operator=(std::nullptr_t rhs) -> Ref<T>&;

	template <typename U>
	inline auto operator=(U* rhs) -> Ref<T>&;

	template <typename U>
	inline auto operator=(const Ref<U>& rhs) -> Ref<T>&;

	/// Cast Ref<A> to Ref<B>
	template <typename U>
	constexpr auto to() const -> Ref<U>;

	/// Obtain the raw pointer
	constexpr auto raw() const -> T*;

	constexpr auto operator==(std::nullptr_t rhs) const -> bool;

	template <typename U>
	constexpr auto operator==(const Ref<U>& rhs) const -> bool;

	template <typename U>
	constexpr auto operator==(U* rhs) const -> bool;

	constexpr explicit operator Pith::Address() const;

	template <typename U>
	constexpr explicit operator U*() const;

private:
	T* value_;
};

}  // namespace Om
}  // namespace OMR

#endif  // OMR_OM_MEMBERREF_HPP_