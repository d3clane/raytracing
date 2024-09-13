#ifndef TYPE_ERASURE_HPP
#define TYPE_ERASURE_HPP

namespace MyTypeErasure
{

struct TypeErasureData
{
    using TypeErasureFuncType = void* (*)(void* data);
    using TypeErasureDtorType = void  (*)(void* data);

    void* data;

    TypeErasureData(
        void* initData, TypeErasureFuncType ctor, 
        TypeErasureDtorType dtor, TypeErasureFuncType assignOperator
    );

    TypeErasureData(const TypeErasureData& other, TypeErasureFuncType copyCtor);

    TypeErasureData& operator =(const TypeErasureData& other);
    ~TypeErasureData();

private:
    TypeErasureDtorType dtor_;
    TypeErasureFuncType assignOperator_;
};

struct TypeErasureFuncWithParams
{
    void (*func)(TypeErasureData params);
    TypeErasureData params;

    void operator()(void) { func(params); }
};

} // namespace MyTypeErasure

#endif // TYPE_ERASURE_HPP