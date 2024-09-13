#include <assert.h>

#include "Other/TypeErasure.hpp"

namespace MyTypeErasure
{

TypeErasureData::TypeErasureData(
    void* initData, TypeErasureFuncType ctor, 
    TypeErasureDtorType dtor, TypeErasureFuncType assignOperator
) : dtor_(dtor), assignOperator_(assignOperator)
{
    if (initData == nullptr)
        return;
    
    assert(initData);

    if (!ctor)
        data = initData;
    else
        data = ctor(initData);
}

TypeErasureData::TypeErasureData(const TypeErasureData& other, TypeErasureFuncType copyCtor)
{
    if (!copyCtor)
    {
        assert(!other.dtor_);
        assert(!other.assignOperator_);

        data = other.data;
        return;
    }

    data = copyCtor(other.data);
    
    assert(other.dtor_);
    assert(other.assignOperator_);

    dtor_           = other.dtor_;
    assignOperator_ = other.assignOperator_;
}

TypeErasureData& TypeErasureData::operator =(const TypeErasureData& other)
{
    if (this == &other) return *this;

    if (dtor_) dtor_(data);

    dtor_           = other.dtor_;
    assignOperator_ = other.assignOperator_;

    if (!assignOperator_)
        data = other.data;
    else
        data = assignOperator_(other.data);

    return *this;
}

TypeErasureData::~TypeErasureData()
{
    if (!dtor_) return;

    dtor_(data);
}

} // namespace MyTypeErasure