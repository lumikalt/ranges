#pragma once

#include <ranges>
#include <functional>

namespace lk {
/* FOLDS */

namespace internal {
	template<std::input_iterator I,
			std::sentinel_for<I> S,
			typename F,
			std::movable Init = std::iter_value_t<I>>
	[[nodiscard]] constexpr
	auto fold(I first, S last, Init init, F f)
	-> Init {
		while ( first != last ) {
			init = std::invoke(f, std::move(init), *first);
			++first;
		}

		return init;
	}
}

using namespace internal;

template<std::ranges::input_range R,
		 typename F,
		 std::movable Init = std::ranges::range_value_t<R>>
[[nodiscard]] constexpr
auto fold_left(R&& rng, Init init, F f)
-> Init {
	return fold(std::ranges::begin(rng),
				std::ranges::end(rng),
				std::move(init),
				std::move(f));
}

template<std::ranges::input_range R,
		 typename F,
		 typename Ret = std::ranges::range_value_t<R>>
[[nodiscard]] constexpr
auto fold_left_first(R&& rng, F f)
-> Ret {
	return fold(std::next(std::ranges::begin(rng)),
				std::ranges::end(rng),
				*std::ranges::begin(rng),
				std::move(f));
}

template<std::ranges::input_range R,
		 typename F,
		 std::movable Init = std::ranges::range_value_t<R>>
[[nodiscard]] constexpr
auto fold_right(R&& rng, Init init, F f)
-> Init {
	return fold(std::ranges::rbegin(rng),
				std::ranges::rend(rng),
				std::move(init),
				std::move(f));
}

template<std::ranges::input_range R,
		 typename F,
		 typename Ret = std::ranges::range_value_t<R>>
[[nodiscard]] constexpr
auto fold_right_first(R&& rng, F f)
-> Ret {
	return fold(std::next(std::ranges::rbegin(rng)),
				std::ranges::rend(rng),
				*std::ranges::rbegin(rng),
				std::move(f));
}

template<std::ranges::input_range R,
		 std::movable Init = std::ranges::range_value_t<R>>
[[nodiscard]] constexpr
auto product(R&& rng, Init init = 1)
-> Init {
	return fold(std::ranges::begin(rng),
				std::ranges::end(rng),
				std::move(init),
				std::move(std::multiplies{}));
}

template<std::ranges::input_range R,
		 std::default_initializable Init = std::ranges::range_value_t<R>>
[[nodiscard]] constexpr
auto sum(R&& rng, Init init = {})
-> Init {
	return fold(std::ranges::begin(rng),
				std::ranges::end(rng),
				std::move(init),
				std::move(std::plus{}));
}

/* FOLDS */
}