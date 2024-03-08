#pragma once

namespace milk {
    template <typename _type> class optional {
        _type _value;
        bool _has_value;

      public:
        optional() : _value(), _has_value(false) {}
        optional(const _type& value) : _value(value), _has_value(true) {}

        constexpr auto value() const { return _value; }
        constexpr auto& value_ref() { return _value; }
        constexpr const auto& value_ref() const { return _value; }
        constexpr auto value_or(_type value) const { return _has_value ? _value : value; }
        constexpr auto has_value() const { return _has_value; }
    };
} // namespace milk
