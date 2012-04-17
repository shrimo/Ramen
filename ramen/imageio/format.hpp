// Copyright (c) 2010 Esteban Tovagliari

#ifndef RAMEN_IMAGEIO_FORMAT_HPP
#define	RAMEN_IMAGEIO_FORMAT_HPP

#include<string>
#include<vector>
#include<memory>

//#include<boost/cstdint.hpp>

#include<ramen/imageio/reader.hpp>
#include<ramen/imageio/writer.hpp>

namespace ramen
{
namespace imageio
{

struct RAMEN_API format_t
{
    format_t();
    virtual ~format_t();

    virtual bool input() const  { return true;}
    virtual bool output() const { return true;}

    virtual std::string tag() const = 0;

    virtual bool check_extension( const std::string& str) const;
    virtual void add_extensions( std::vector<std::string>& ext) const = 0;

    virtual std::size_t detect_size() const;
    virtual bool detect( const char *p) const;

    virtual bool is_multichannel() const;

    virtual std::auto_ptr<reader_t> reader( const boost::filesystem::path& p) const;
    virtual std::auto_ptr<writer_t> writer() const;
};

} // namespace
} // namespace

#endif