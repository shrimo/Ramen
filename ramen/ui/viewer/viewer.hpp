// Copyright (c) 2010 Esteban Tovagliari

#ifndef RAMEN_UI_VIEWER_HPP
#define	RAMEN_UI_VIEWER_HPP

#include<string>
#include<vector>
#include<map>

#include<loki/Singleton.h>

#include<QObject>

#include<map>

#include<boost/function.hpp>

#include<ramen/nodes/node_fwd.hpp>

#include<ramen/ui/viewer/viewer_strategy_fwd.hpp>
#include<ramen/ui/viewer/viewer_context_fwd.hpp>

#include<ramen/ui/widgets/double_spinbox_fwd.hpp>

class QWidget;
class QFrame;
class QPushButton;
class QComboBox;
class QDoubleSpinBox;
class QToolButton;
class QLabel;

class QrContainerWidget;

namespace ramen
{
namespace ui
{

class viewer_impl : public QObject
{
    Q_OBJECT

public:

	int width() const;
	int height() const;
	
    void init();

    QWidget *widget() { return window_;}

    int toolbar_height() const;

    void set_viewer_toolbar( QWidget *w);

    void set_active_node( node_t *n);
    void set_context_node( node_t *n);

    void node_added( node_t *n);
    void node_released( node_t *n);

    void frame_changed();

    void set_status( const std::string& text);

    // ocio
    const std::string& display_device() const;
    const std::string& display_transform() const;
	
	float exposure() const;
	float gamma() const;
	
	void update_display_transform();
	
	// access to current viewer strategy
	const viewer::viewer_strategy_t& current_viewer() const;
	viewer::viewer_strategy_t& current_viewer();	
	
	void update() const;
	void swap_buffers();

	void begin_interaction();
	void end_interaction();

public Q_SLOTS:

     void autoupdate_toggle( bool state);
     void change_active_context_view( int index);

     void change_display_device( int index);
     void change_display_transform( int index);

     void change_exposure( double d);
	 void change_gamma( double d);

private:

    viewer_impl();
	~viewer_impl();

    void get_display_devices();
    void get_display_transforms();
    
    friend struct Loki::CreateUsingNew<viewer_impl>;

    QWidget *window_;
    int toolbar_height_;

    QLabel *status_;
    viewer::viewer_context_t *view_;
    QrContainerWidget *active_toolbar_;
    QrContainerWidget *viewer_toolbar_;

    QToolButton *update_btn_;
    QComboBox *result_combo_;
    QComboBox *ocio_device_combo_;
    QComboBox *ocio_transform_combo_;
	
    double_spinbox_t *exposure_input_;
    double_spinbox_t *gamma_input_;

    // toolbars
    std::map<node_t*, QWidget*> node_toolbars_;
    std::map<node_t*, QWidget*>::iterator current_node_toolbar_;

    // OpenColorIO
    std::vector<std::string> display_devices_;
    std::vector<std::string> display_transforms_;
    std::string display_device_;
    std::string display_transform_;
};

typedef Loki::SingletonHolder<viewer_impl> viewer_t;

} // ui
} // ramen

#endif