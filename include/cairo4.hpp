// MIT License
//
// Copyright (c) 2022 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
// cairo4cpp - a work-in-progress cairo wrapper
// ---------
// github.com/ferhatgec/cairo4cpp

#ifndef CAIRO4CPP_CAIRO4_HPP
#define CAIRO4CPP_CAIRO4_HPP

#include <string>

#ifdef __has_include
    #if __has_include(<cairo/cairo.h>)
        #include <cairo/cairo.h>
    #elif __has_include(<cairo.h>)
        #include <cairo.h>
    #else
        #error "libcairo not found."
    #endif
#endif // __has_include

#define WRAP_CLASS(name, data) \
class name {                   \
public:                               \
data init;                     \
};

#define ne noexcept

#define WRAP_FUNC(name, impl) \
void impl() ne {              \
    name(this->init);         \
}

namespace cairo4 {
    #define raw_cairo4 cairo_t

    WRAP_CLASS(surface, cairo_surface_t*)
    WRAP_CLASS(pattern, cairo_pattern_t*)
    WRAP_CLASS(rectangle_list, cairo_rectangle_list_t*)
    WRAP_CLASS(user_data_key, cairo_user_data_key_t*)
    WRAP_CLASS(path, cairo_path_t*)
    WRAP_CLASS(glyph, cairo_glyph_t*)
    WRAP_CLASS(rectangle_int, cairo_rectangle_int_t*)
    WRAP_CLASS(font_type, cairo_font_type_t)
    WRAP_CLASS(line_cap, cairo_line_cap_t)
    WRAP_CLASS(antialias, cairo_antialias_t)
    WRAP_CLASS(fill_rule, cairo_fill_rule_t)
    WRAP_CLASS(cstatus, cairo_status_t)
    WRAP_CLASS(content, cairo_content_t)
    WRAP_CLASS(line_join, cairo_line_join_t)
    WRAP_CLASS(coperator, cairo_operator_t)
    WRAP_CLASS(cbool, cairo_bool_t)
    WRAP_CLASS(destroy_func, cairo_destroy_func_t)
    WRAP_CLASS(region_overlap, cairo_region_overlap_t)

    class matrix {
    public:
        cairo_matrix_t* init = nullptr;
    public:
        matrix() = default; ~matrix() = default;

        void initm(double xx, double yx, double xy, double yy, double x0, double y0) ne {
            cairo_matrix_init(this->init, xx, yx, xy, yy, x0, y0);
        }

        void init_identity() ne {
            cairo_matrix_init_identity(this->init);
        }

        void init_translate(double tx, double ty) ne {
            cairo_matrix_init_translate(this->init, tx, ty);
        }

        void init_scale(double sx, double sy) ne {
            cairo_matrix_init_scale(this->init, sx, sy);
        }

        void init_rotate(double rad) ne {
            cairo_matrix_init_rotate(this->init, rad);
        }

        void translate(double tx, double ty) ne {
            cairo_matrix_translate(this->init, tx, ty);
        }

        void scale(double sx, double sy) ne {
            cairo_matrix_scale(this->init, sx, sy);
        }

        void rotate(double rad) ne {
            cairo_matrix_rotate(this->init, rad);
        }

        cstatus invert() ne {
            return cstatus {
                cairo_matrix_invert(this->init)
            };
        }

        void multiply(const matrix x, const matrix y) ne {
            cairo_matrix_multiply(this->init, x.init, y.init);
        }

        void transform_distance(double* dx, double* dy) ne {
            cairo_matrix_transform_distance(this->init, dx, dy);
        }

        void transform_point(double* x, double* y) ne {
            cairo_matrix_transform_point(this->init, x, y);
        }
    };

    class cairo {
    public:
        cairo_t* init = nullptr;
    public:
        cairo() = default;
        cairo(raw_cairo4* x) : init(x) {}
        ~cairo() {
            this->destroy();
        }

        WRAP_FUNC(cairo_destroy, destroy)
        WRAP_FUNC(cairo_save, save)
        WRAP_FUNC(cairo_restore, restore)
        WRAP_FUNC(cairo_push_group, push_group)
        WRAP_FUNC(cairo_pop_group_to_source, pop_group_to_source)
        WRAP_FUNC(cairo_clip, clip)
        WRAP_FUNC(cairo_clip_preserve, clip_preserve)
        WRAP_FUNC(cairo_reset_clip, reset_clip)
        WRAP_FUNC(cairo_fill, fill)
        WRAP_FUNC(cairo_fill_preserve, fill_preserve)
        WRAP_FUNC(cairo_paint, paint)
        WRAP_FUNC(cairo_stroke, stroke)
        WRAP_FUNC(cairo_stroke_preserve, stroke_preserve)
        WRAP_FUNC(cairo_copy_page, copy_page)
        WRAP_FUNC(cairo_show_page, show_page)

        void create(surface x) ne {
            this->init = cairo_create(x.init);
        }

        void reference(cairo x) ne {
            this->init = cairo_reference(x.init);
        }

        cstatus status() ne {
            cstatus x;

            x.init = cairo_status(this->init);
            return x;
        }

        surface get_target() ne {
            return surface {
                cairo_get_target(this->init)
            };
        }


        void push_group_with_content(content x) ne {
            cairo_push_group_with_content(this->init, x.init);
        }

        pattern pop_group() ne {
            return pattern {
                cairo_pop_group(this->init)
            };
        }

        surface get_group_target() ne {
            return surface {
                cairo_get_group_target(this->init)
            };
        }

        void set_source_rgb(double r, double g, double b) ne {
            cairo_set_source_rgb(this->init, r, g, b);
        }

        void set_source_rgba(double r, double g, double b, double a) ne {
            cairo_set_source_rgba(this->init, r, g, b, a);
        }

        void set_source(pattern x) ne {
            cairo_set_source(this->init, x.init);
        }

        void set_source_surface(surface x, double xx, double yy) ne {
            cairo_set_source_surface(this->init, x.init, xx, yy);
        }

        pattern get_source() ne {
            return pattern {
                cairo_get_source(this->init)
            };
        }

        void set_antialias(antialias x) ne {
            cairo_set_antialias(this->init, x.init);
        }

        antialias get_antialias() ne {
            return antialias {
                cairo_get_antialias(this->init)
            };
        }

        void set_dash(const double* dashes, int num_dashes, double offset) ne {
            cairo_set_dash(this->init, dashes, num_dashes, offset);
        }

        int get_dash_count() ne {
            return cairo_get_dash_count(this->init);
        }

        void get_dash(double* dashes, double* offset) ne {
            cairo_get_dash(this->init, dashes, offset);
        }

        void set_fill_rule(fill_rule x) ne {
            cairo_set_fill_rule(this->init, x.init);
        }

        fill_rule get_fill_rule() ne {
            return fill_rule {
                cairo_get_fill_rule(this->init)
            };
        }

        void set_line_cap(line_cap x) ne {
            cairo_set_line_cap(this->init, x.init);
        }

        line_cap get_line_cap() ne {
            return line_cap {
                cairo_get_line_cap(this->init)
            };
        }

        void set_line_join(line_join x) ne {
            cairo_set_line_join(this->init, x.init);
        }

        line_join get_line_join() ne {
            return line_join {
                cairo_get_line_join(this->init)
            };
        }

        void set_line_width(double width) ne {
            cairo_set_line_width(this->init, width);
        }

        double get_line_width()  ne {
            return cairo_get_line_width(this->init);
        }

        void set_miter_limit(double limit) ne {
            cairo_set_miter_limit(this->init, limit);
        }

        double get_miter_limit() ne {
            return cairo_get_miter_limit(this->init);
        }

        void set_operator(coperator x) ne {
            cairo_set_operator(this->init, x.init);
        }

        coperator get_operator() ne {
            return coperator {
                cairo_get_operator(this->init)
            };
        }

        void set_tolerance(double tolerance) ne {
            cairo_set_tolerance(this->init, tolerance);
        }

        double get_tolerance() ne {
            return cairo_get_tolerance(this->init);
        }

        void clip_extents(double* x1, double* y1, double* x2, double* y2) ne {
            cairo_clip_extents(this->init, x1, y1, x2, y2);
        }

        cbool in_clip(double x, double y) ne {
            return cbool {
                cairo_in_clip(this->init, x, y)
            };
        }

        void rectangle_list_destroy(rectangle_list x) ne {
            cairo_rectangle_list_destroy(x.init);
        }

        rectangle_list copy_clip_rectangle_list() ne {
            return rectangle_list {
                cairo_copy_clip_rectangle_list(this->init)
            };
        }

        void fill_extents(double* x1, double* y1, double* x2, double* y2) ne {
            cairo_fill_extents(this->init, x1, y1, x2, y2);
        }

        cbool in_fill(double x, double y) ne {
            return cbool {
                cairo_in_fill(this->init, x, y)
            };
        }

        void mask(pattern x) ne {
            cairo_mask(this->init, x.init);
        }

        void mask_surface(surface x, double sur_x, double sur_y) ne {
            cairo_mask_surface(this->init, x.init, sur_x, sur_y);
        }

        void paint_with_alpha(double a) ne {
            cairo_paint_with_alpha(this->init, a);
        }

        void stroke_events(double* x1, double* y1, double* x2, double* y2) ne {
            cairo_stroke_extents(this->init, x1, y1, x2, y2);
        }

        cbool in_stroke(double x, double y) ne {
            return cbool {
                cairo_in_stroke(this->init, x, y)
            };
        }

        unsigned get_reference_count() ne {
            return cairo_get_reference_count(this->init);
        }

        template<typename Data>
        cstatus set_user_data(const  user_data_key key,
                                                            Data user_data,
                                                            destroy_func destroy) ne {
            return cstatus {
                cairo_set_user_data(this->init, key.init, user_data, destroy.init)
            };
        }

        template<typename Data>
        Data get_user_data(const user_data_key key) ne {
            return cairo_get_user_data(this->init, key.init);
        }

        path copy_path() ne {
            return path {
                cairo_copy_path(this->init)
            };
        }

        path copy_path_flat() ne {
            return path {
                cairo_copy_path_flat(this->init)
            };
        }

        void path_destroy(path x) ne {
            cairo_path_destroy(x.init);
        }

        void append(const path x) ne {
            cairo_append_path(this->init, x.init);
        }

        cbool has_current_point() ne {
            return cbool {
                cairo_has_current_point(this->init)
            };
        }

        void get_current_point(double* x, double* y) ne {
            cairo_get_current_point(this->init ,x, y);
        }

        WRAP_FUNC(cairo_new_path, new_path)
        WRAP_FUNC(cairo_new_sub_path, new_sub_path)
        WRAP_FUNC(cairo_close_path, close_path)

        void arc(double xc, double yc, double rad, double a1, double a2) ne {
            cairo_arc(this->init, xc, yc, rad, a1, a2);
        }

        void arc_negative(double xc, double yc, double rad, double a1, double a2) ne {
            cairo_arc_negative(this->init, xc, yc, rad, a1, a2);
        }

        void curve_to(double x1, double y1, double x2, double y2, double x3, double y3) ne {
            cairo_curve_to(this->init, x1, y1, x2, y2, x3, y3);
        }

        void line_to(double x, double y) ne {
            cairo_line_to(this->init, x, y);
        }

        void move_to(double x, double y) ne {
            cairo_move_to(this->init, x, y);
        }

        void rectangle(double x, double y, double w, double h) ne {
            cairo_rectangle(this->init, x, y, w, h);
        }

        void glyph_path(const glyph x, int n) ne {
            cairo_glyph_path(this->init, x.init, n);
        }

        void text_path(const std::string utf8) ne {
            cairo_text_path(this->init, utf8.c_str());
        }

        void rel_curve_to(double dx1, double dy1, double dx2, double dy2, double dx3, double dy3) ne {
            cairo_rel_curve_to(this->init, dx1, dy1, dx2, dy2, dx3, dy3);
        }

        void rel_line_to(double dx, double dy) ne {
            cairo_rel_line_to(this->init, dx, dy);
        }

        void rel_move_to(double dx, double dy) ne {
            cairo_rel_move_to(this->init, dx, dy);
        }

        void path_extents(double* x1, double* y1, double* x2, double* y2) ne {
            cairo_path_extents(this->init, x1, y1, x2, y2);
        }

        void translate(double tx, double ty) ne {
            cairo_translate(this->init, tx, ty);
        }

        void scale(double sx, double sy) ne {
            cairo_scale(this->init, sx, sy);
        }

        void rotate(double angle) ne {
            cairo_rotate(this->init, angle);
        }

        void transform(const matrix x) ne {
            cairo_transform(this->init , x.init);
        }

        void set_matrix(const matrix x) ne {
            cairo_set_matrix(this->init, x.init);
        }

        void get_matrix(matrix x) ne {
            cairo_get_matrix(this->init, x.init);
        }

        void identity_matrix() ne {
            cairo_identity_matrix(this->init);
        }

        void user_to_device(double* x, double* y) ne {
            cairo_user_to_device(this->init, x, y);
        }

        void user_to_device_distance(double* dx, double* dy) ne {
            cairo_user_to_device_distance(this->init, dx, dy);
        }

        void device_to_user(double* x, double* y) ne {
            cairo_device_to_user(this->init, x, y);
        }

        void device_to_user_distance(double* dx, double* dy) ne {
            cairo_device_to_user_distance(this->init, dx, dy);
        }

        void tag_begin(const std::string tag_name,
                                        const std::string attrs) ne {
            cairo_tag_begin(this->init, tag_name.c_str(), attrs.c_str());
        }

        void tag_end(const std::string tag_name) ne {
            cairo_tag_end(this->init, tag_name.c_str());
        }
    };

    class region {
        cairo_region_t* init = nullptr;
    public:
        region() = default; ~region() {
            this->destroy();
        }

        WRAP_FUNC(cairo_region_destroy, destroy)

        void create() ne {
            this->init = cairo_region_create();
        }

        void create_rectangle(const rectangle_int x) ne {
            this->init = cairo_region_create_rectangle(x.init);
        }

        void create_rectangles(const rectangle_int x, int n) ne {
            this->init = cairo_region_create_rectangles(x.init, n);
        }

        void copy(const region x) ne {
            this->init = cairo_region_copy(x.init);
        }

        void reference(const region x) ne {
            this->init = cairo_region_reference(x.init);
        }

        cstatus status() ne {
            return cstatus {
                cairo_region_status(this->init)
            };
        }

        void get_extents(rectangle_int x) ne {
            cairo_region_get_extents(this->init, x.init);
        }

        int num_rectangles() ne {
            return cairo_region_num_rectangles(this->init);
        }

        void get_rectangle(int nth, rectangle_int x) ne {
            cairo_region_get_rectangle(this->init, nth, x.init);
        }

        cbool is_empty() ne {
            return cbool {
                cairo_region_is_empty(this->init)
            };
        }

        cbool contains_point(int x, int y) ne {
            return cbool {
                cairo_region_contains_point(this->init, x, y)
            };
        }

        region_overlap contains_rectangle(const rectangle_int x) ne {
            return region_overlap {
                cairo_region_contains_rectangle(this->init, x.init)
            };
        }

        cbool equal(const region x) ne {
            return cbool {
                cairo_region_equal(this->init, x.init)
            };
        }

        void translate(int dx, int dy) ne {
            cairo_region_translate(this->init, dx, dy);
        }

        cstatus intersect(const region x) ne {
            return cstatus {
                cairo_region_intersect(this->init, x.init)
            };
        }

        cstatus intersect_rectangle(const rectangle_int x) ne {
            return cstatus {
                cairo_region_intersect_rectangle(this->init, x.init)
            };
        }

        cstatus subtract(const region x) ne {
            return cstatus {
                cairo_region_subtract(this->init , x.init)
            };
        }

        cstatus subtract_rectangle(const rectangle_int x) ne {
            return cstatus {
                cairo_region_subtract_rectangle(this->init, x.init)
            };
        }

        cstatus reg_union(const region x) ne {
            return cstatus {
                cairo_region_union(this->init, x.init)
            };
        }

        cstatus reg_union_rectangle(const rectangle_int x) ne {
            return cstatus {
                cairo_region_union_rectangle(this->init, x.init)
            };
        }

        cstatus reg_xor(const region x) ne {
            return cstatus {
                cairo_region_xor(this->init, x.init)
            };
        }

        cstatus reg_xor_rectangle(const rectangle_int x) ne {
            return cstatus {
                cairo_region_xor_rectangle(this->init, x.init)
            };
        }
    };

    class font_face {
        cairo_font_face_t* init = nullptr;
    public:
        font_face() = default; ~font_face() {
            this->destroy();
        }

        WRAP_FUNC(cairo_font_face_destroy, destroy)

        void reference(font_face x) ne {
            this->init = cairo_font_face_reference(x.init);
        }

        cstatus status() ne {
            return cstatus {
                cairo_font_face_status(this->init)
            };
        }

        font_type get_type() ne {
            return font_type {
                cairo_font_face_get_type(this->init)
            };
        }

        unsigned get_reference_count() ne {
            return cairo_font_face_get_reference_count(this->init);
        }

        template<typename Data>
        cstatus set_user_data(const user_data_key x,
                                                            Data user_data,
                                                            destroy_func dest) ne {
            return cstatus {
                cairo_font_face_set_user_data(this->init, x.init, user_data, dest.init)
            };
        }

        template<typename Data>
        Data get_user_data(const user_data_key x) ne {
            return cairo_font_face_get_user_data(this->init, x.init);
        }

        #ifdef CAIRO_HAS_QUARTZ_FONT
            void create_for_cgfont(CGFontRef x) ne {
                this->init = cairo_quartz_font_face_create_for_cgfont(x);
            }

            void create_for_atsu_font_id(ATSUFontID x) ne {
                this->init = cairo_quartz_font_face_create_for_atsu_font_id(x);
            }
        #endif // CAIRO_HAS_QUARTZ_FONT
    };

    const std::string status_to_string(cstatus x) ne {
        return std::string(cairo_status_to_string(x.init));
    }

    void debug_reset_static_data() ne {
        cairo_debug_reset_static_data();
    }

    unsigned version() ne {
        return cairo_version();
    }

    const std::string version_string() ne {
        return std::to_string(cairo_version());
    }
}

#undef WRAP_FUNC
#undef WRAP_CLASS
#undef ne
#endif // CAIRO4CPP_CAIRO4_HPP
