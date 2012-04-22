// Copyright (c) 2010 Esteban Tovagliari

#ifndef RAMEN_IMAGEIO_FACTORY_HPP
#define	RAMEN_IMAGEIO_FACTORY_HPP

#include<vector>
#include<string>

#include<boost/noncopyable.hpp>
#include<boost/ptr_container/ptr_vector.hpp>

#include<ramen/imageio/exceptions.hpp>
#include<ramen/imageio/enums.hpp>
#include<ramen/imageio/format.hpp>

#include<ramen/image/typedefs.hpp>

namespace ramen
{
namespace imageio
{

class factory_t : boost::noncopyable
{
public:

    static factory_t& instance();

    ~factory_t();

    const boost::ptr_vector<format_t>& formats() const { return formats_;}

    typedef boost::ptr_vector<format_t>::const_iterator const_iterator;

    const_iterator begin() const    { return formats_.begin();}
    const_iterator end() const	    { return formats_.end();}

    bool register_image_format( std::auto_ptr<format_t> format);

    const std::vector<std::string>& extensions() const  { return extensions_;}

	bool is_image_file( const boost::filesystem::path& p) const;
	bool is_image_format_tag( const std::string& tag) const;
	
    std::auto_ptr<reader_t> reader_for_image( const boost::filesystem::path& p) const;
    std::auto_ptr<writer_t> writer_for_tag( const std::string& tag) const;

private:

    factory_t();

    const_iterator format_for_tag( const std::string& tag) const;
    const_iterator format_for_extension( const boost::filesystem::path& p) const;
    const_iterator format_for_file_contents( const boost::filesystem::path& p) const;

    boost::ptr_vector<format_t> formats_;
    std::vector<std::string> extensions_;

    std::size_t detect_size_;
    mutable char *detect_buffer_;
};

} // namespace
} // namespace

#endif
