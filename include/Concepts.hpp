//
// Created by Aleksej on 23.04.2023.
//

#ifndef TRANSLATOR_CONCEPTS_HPP
#define TRANSLATOR_CONCEPTS_HPP

#include <type_traits>

template<class BaseClass, typename Type>
concept Derived = std::is_base_of<BaseClass, Type>::value;

#endif //TRANSLATOR_CONCEPTS_HPP
