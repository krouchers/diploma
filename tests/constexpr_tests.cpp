
template <bool B>
bool static_test()
{
    static_assert(B);
    return B;
}
#define TEST(X) static_test<X>()