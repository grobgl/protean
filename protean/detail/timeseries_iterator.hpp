#ifndef PROTEAN_DETAIL_TIMESERIES_ITERATOR_HPP
#define PROTEAN_DETAIL_TIMESERIES_ITERATOR_HPP

#include <protean/config.hpp>
#include <protean/variant_error.hpp>

#if defined(_MSC_VER)
#    pragma warning(push)
#    pragma warning(disable:4251)
#endif

namespace protean { namespace detail {

    template<
        typename ITERATOR_TRAITS
      , typename BASE=variant_iterator_interface<ITERATOR_TRAITS>
    >
    class PROTEAN_DECL timeseries_iterator_interface : public BASE
    {
        typedef typename ITERATOR_TRAITS::value_type& reference;
        typedef typename ITERATOR_TRAITS::timeseries_iterator_type iterator_type;
        typedef typename BASE::date_time_t date_time_t;

    public:
        timeseries_iterator_interface(const iterator_type& iterator) :
            m_iterator(iterator)
        {
        }
        const std::string& key() const
        {
            boost::throw_exception (variant_error ("Attempt to call key() on timeseries iterator"));
        }
        reference value() const
        {
            return m_iterator->second;
        }
        const date_time_t& time() const
        {
            return m_iterator->first;
        }
        void increment()
        {
            ++m_iterator;
        }
        void decrement()
        {
            --m_iterator;
        }
        bool equal(const variant_const_iterator_base *rhs) const
        {
            const timeseries_iterator_interface<const_iterator_traits>* cast_rhs =
                dynamic_cast<const timeseries_iterator_interface<const_iterator_traits>*>(rhs);

            if (cast_rhs==nullptr)
            {
                boost::throw_exception (variant_error ("Unable to convert iterator to timeseries iterator"));
            }
            return m_iterator==cast_rhs->iterator();
        }
        iterator_type iterator() const
        {
            return m_iterator;
        }
        BASE* clone()
        {
            return new timeseries_iterator_interface(m_iterator);
        }
        variant_const_iterator_base* to_const() const
        {
            return new timeseries_iterator_interface<const_iterator_traits>(m_iterator);
        }

    private:
        iterator_type m_iterator;
    };    

    typedef timeseries_iterator_interface<iterator_traits> timeseries_iterator;
    typedef timeseries_iterator_interface<const_iterator_traits> timeseries_const_iterator;

}} // namespace protean::detail

#if defined(_MSC_VER)
#    pragma warning(pop)
#endif

#endif // PROTEAN_DETAIL_TIMESERIES_ITERATOR_HPP
