#include "Defines.h"
#include <float.h>

namespace Mishka
{
    /**
     * \brief Set of type properties.
     *
     * \tparam T
     */
    template<typename T>
    struct TypeBase
    {
        /**
         * \brief Sizeof type
         */
        static inline const u32 size = sizeof(T);

        /**
         * \brief Name of type if was native. "Unknown" for custom types like classes and enums.
         */
        static inline const char* name = "Unknown";

        /**
         * \brief Type id name.
         */
        static inline const char* typeName = typeid(T).name();

        /**
         * \brief Type raw name.
         */
        static inline const char* rawName = typeid(T).raw_name();

        /**
         * \brief Type id hash.
         */
        static inline u64 hash = typeid(T).hash_code();

        /**
         * \brief Minimum possilbe value for numeric types.
         */
        static inline u32 min = 0;

        /**
         * \brief Maximum possilbe value for numeric types.
         */
        static inline u32 max = 0;

        /**
         * \brief Is type signed for numeric types.
         */
        static inline bool isSigned = false;

        /**
         * \brief Is type unsigned for numeric types.
         */
        static inline bool isUnsigned = false;

        /**
         * \brief Is type integral for numeric types.
         */
        static inline bool isIntegral = false;

        /**
         * \brief Is type real for numeric types.
         */
        static inline bool isFloat = false;

        /**
         * \brief Is type a custom class.
         */
        static inline bool isClass = __is_class(T);

        /**
         * \brief Is type a custom union.
         */
        static inline bool isUnion = __is_union(T);

        /**
         * \brief Is type a custom enum.
         */
        static inline bool isEnum = __is_enum(T);
    };

    template<typename T>
    struct Type : public TypeBase<T>
    {};

    /* ---------------------------- Signed Integrals ---------------------------- */

    template<>
    struct Type<char>: TypeBase<char>
    {
        static inline const char* name = "char";
        static inline const char max =  0x7f;
        static inline const char min = -0x80;
        static inline bool isIntegral = true;
        static inline bool isSigned = true;
    };

    template<>
    struct Type<signed char>: TypeBase<signed char>
    {
        static inline const char* name = "signed char";
        static inline const char max =  0x7f;
        static inline const char min = -0x80;
        static inline bool isIntegral = true;
        static inline bool isSigned = true;
    };

    template<>
    struct Type<short int>: TypeBase<short int>
    {
        static inline const char* name = "short int";
        static inline const short int max =  0x7fff;
        static inline const short int min = -0x8000;
        static inline bool isIntegral = true;
        static inline bool isSigned = true;
    };

    template<>
    struct Type<int>: TypeBase<int>
    {
        static inline const char* name = "int";
        static inline const int max =  0x7fffffff;
        static inline const int min = -0x7fffffff - 1;
        static inline bool isIntegral = true;
        static inline bool isSigned = true;
    };

    template<>
    struct Type<long int>: TypeBase<long int>
    {
        static inline const char* name = "long int";
        static inline const int max =  0x7fffffff;
        static inline const int min = -0x7fffffff - 1;
        static inline bool isIntegral = true;
        static inline bool isSigned = true;
    };

    template<>
    struct Type<long long int>: TypeBase<long long int>
    {
        static inline const char* name = "long long int";
        static inline const long long int max =  0x7fffffffffffffff;
        static inline const long long int min = -0x7fffffffffffffff - 1;
        static inline bool isIntegral = true;
        static inline bool isSigned = true;
    };

    /* --------------------------- Unsinged Integrals --------------------------- */

    template<>
    struct Type<unsigned char>: TypeBase<unsigned char>
    {
        static inline const char* name = "unsigned char";
        static inline const unsigned char min = 0;
        static inline const unsigned char max = 0xff;
        static inline bool isUnsigned = true;
        static inline bool isIntegral = true;
    };

    template<>
    struct Type<unsigned short int>: TypeBase<unsigned short int>
    {
        static inline const char* name = "unsigned short int";
        static inline const unsigned short int min = 0;
        static inline const unsigned short int max = 0xffff;
        static inline bool isUnsigned = true;
        static inline bool isIntegral = true;
    };

    template<>
    struct Type<unsigned int>: TypeBase<unsigned int>
    {
        static inline const char* name = "unsigned int";
        static inline const unsigned int min = 0;
        static inline const unsigned int max = 0xffffffff;
        static inline bool isUnsigned = true;
        static inline bool isIntegral = true;
    };

    template<>
    struct Type<unsigned long int>: TypeBase<unsigned long int>
    {
        static inline const char* name = "unsigned long int";
        static inline const unsigned int min = 0;
        static inline const unsigned int max = 0xffffffff;
        static inline bool isUnsigned = true;
        static inline bool isIntegral = true;
    };

    template<>
    struct Type<unsigned long long int>: TypeBase<unsigned long long int>
    {
        static inline const char* name = "unsigned long long int";
        static inline const unsigned long long int min = 0;
        static inline const unsigned long long int max = 0xffffffffffffffff;
        static inline bool isUnsigned = true;
        static inline bool isIntegral = true;
    };

    /* ----------------------------- Floating point ----------------------------- */

    template<>
    struct Type<float>: TypeBase<float>
    {
        static inline const char* name = "float";
        static inline const float max = FLT_MAX;
        static inline const float min = FLT_MIN;
        static inline bool isFloat = true;
        static inline bool isSigned = true;
    };

    template<>
    struct Type<double>: TypeBase<double>
    {
        static inline const char* name = "double";
        static inline const double max = DBL_MAX;
        static inline const double min = DBL_MIN;
        static inline bool isFloat = true;
        static inline bool isSigned = true;
    };

    template<>
    struct Type<long double>: TypeBase<long double>
    {
        static inline const char* name = "long double";
        static inline const long double max = LDBL_MAX;
        static inline const long double min = LDBL_MIN;
        static inline bool isFloat = true;
        static inline bool isSigned = true;
    };

    /* ----------------------------- Character Types ---------------------------- */

    template<>
    struct Type<wchar_t>: TypeBase<wchar_t>
    {
        static inline const char* name = "wchar_t";
        static inline const wchar_t max = 0xffff;
        static inline const wchar_t min = 0;
        static inline bool isIntegral = true;
        static inline bool isUnsigned = true;
    };

    template<>
    struct Type<char16_t>: TypeBase<char16_t>
    {
        static inline const char* name = "char16_t";
        static inline const char16_t max = 0xffff;
        static inline const char16_t min = 0;
        static inline bool isIntegral = true;
        static inline bool isUnsigned = true;
    };

    template<>
    struct Type<char32_t>: TypeBase<char32_t>
    {
        static inline const char* name = "char32_t";
        static inline const char32_t max = 0xffffffff;
        static inline const char32_t min = 0;
        static inline bool isIntegral = true;
        static inline bool isUnsigned = true;
    };

}
