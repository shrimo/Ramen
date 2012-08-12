// Copyright (c) 2011 Esteban Tovagliari
// Licensed under the terms of the CDDL License.
// See CDDL_LICENSE.txt for a copy of the license.

#include<ramen/config.hpp>

#include<ramen/python/python.hpp>

#include<vector>

#include<boost/python.hpp>

#include<ramen/assert.hpp>
#include<ramen/version.hpp>

#include<ramen/app/application.hpp>
#include<ramen/app/document.hpp>
#include<ramen/python/interpreter.hpp>

#include<ramen_ui/user_interface.hpp>

#include<iostream>

namespace bpy = boost::python;
using namespace ramen;

namespace ramen
{

struct py_application_access
{
    static void create_dirs( application_t *a)
    {
        a->create_dirs();
    }

    static void init_threads( application_t *a, int num)
    {
        a->init_threads( num);
    }

    static void init_ocio( application_t *a)
    {
        a->init_ocio();
    }

    static void print_app_info( application_t *a)
    {
        a->print_app_info();
    }

    static void set_preferences( application_t *a, boost::python::object prefs)
    {
        a->set_preferences( prefs);
    }

    static void set_ui( application_t *a, ramen_ui::user_interface_t *ui)
    {
        a->set_ui( ui);
    }

    // version, names, ...

    static int version_major( application_t *a) { return RAMEN_VERSION_MAJOR;}
    static int version_minor( application_t *a) { return RAMEN_VERSION_MINOR;}
    static int version_patch( application_t *a) { return RAMEN_VERSION_PATCH;}

    static const char *full_version_name( application_t *a)
    {
        return RAMEN_NAME_FULL_VERSION_STR;
    }

    static int run_unit_tests( application_t *a, bpy::list args)
    {
        // TODO: pass the rest of the arguments here.
        std::string path = bpy::extract<std::string>( args[0]);
        char *s = const_cast<char *>( path.c_str());
        return a->run_unit_tests( 1, &s);
    }
};

} // ramen

namespace
{

bpy::object app_main_namespace( application_t *a)
{
    return python::interpreter_t::instance().main_namespace();
}

document_t& app_get_document( application_t *a)
{
    return a->document();
}

void app_open_document( application_t *a, const std::string& file)
{
    a->open_document( boost::filesystem::path( file));
}

application_t *py_app()
{
    return &app();
}

} // unnamed

void export_application()
{
    bpy::class_<application_t, boost::noncopyable>( "base_application")
        .def( "_create_dirs", &py_application_access::create_dirs)
        .def( "_init_threads", &py_application_access::init_threads)
        .def( "_init_ocio", &py_application_access::init_ocio)
        .def( "_print_app_info", &py_application_access::print_app_info)
        .def( "_set_preferences", &py_application_access::set_preferences)
        .def( "_set_ui", &py_application_access::set_ui)
        .def( "_run_unit_tests", &py_application_access::run_unit_tests)

        .def( "system", &application_t::system, bpy::return_value_policy<bpy::reference_existing_object>())

        .def( "main_namespace", app_main_namespace)

        .def( "version_major", &py_application_access::version_major)
        .def( "version_minor", &py_application_access::version_minor)
        .def( "version_patch", &py_application_access::version_patch)

        .def( "full_version_name", &py_application_access::full_version_name)

        .def( "debug_build", &application_t::debug_build)

        .def( "create_new_document", &application_t::create_new_document)
        .def( "open_document", app_open_document)
        .def( "document", app_get_document, bpy::return_value_policy<bpy::reference_existing_object>())
        ;

    bpy::def( "r_app", py_app, bpy::return_value_policy<bpy::reference_existing_object>());
}
