// Copyright (c) 2010 Esteban Tovagliari
// Licensed under the terms of the CDDL License.
// See CDDL_LICENSE.txt for a copy of the license.

#ifndef RAMEN_UI_CONTAINER_WIDGET_HPP
#define	RAMEN_UI_CONTAINER_WIDGET_HPP

#include<ramen/ui/widgets/container_widget_fwd.hpp>

#include<QStackedWidget>

namespace ramen
{
namespace ui
{

class container_widget_t : public QStackedWidget
{
    Q_OBJECT

public:
    
    container_widget_t( QWidget *parent = 0);

    void set_contents( QWidget *w);
    void clear_contents();

private:

    QWidget *contents_;
};

} // ui
} // ramen

#endif
