








void
E_x_W( void
){  E_x_font_W();
    E_mem_Q_tab_W( E_x_Q_display_S );
    W( E_x_S_wm_icon );
}
void
E_x_font_W( void
){  for_each( id, E_x_Q_font_S, E_mem_Q_tab )
    {   struct E_x_Q_font_Z *font = E_mem_Q_tab_R( E_x_Q_font_S, id );
        for_n( i, font->bitmap_n )
            W( font->bitmap[i].bitmap );
        W( font->bitmap );
    }
    E_mem_Q_tab_W( E_x_Q_font_S );
}


