/*

EC_AD5204_ANSWER dp_update_value ( void ) {
	EC_AD5204_ANSWER    r;
	r = sound_dp.value_set( 0, 0, g.dp.b );
	if ( r != EC_AD5204_ANSWER::OK ) return r;
	r = sound_dp.value_set( 0, 1, g.dp.c );
	if ( r != EC_AD5204_ANSWER::OK ) return r;
	r = sound_dp.value_set( 0, 2, g.dp.a );
	if ( r != EC_AD5204_ANSWER::OK ) return r;
	r = sound_dp.value_set( 0, 3, g.dp.a1 );
	if ( r != EC_AD5204_ANSWER::OK ) return r;
	r = sound_dp.value_set( 1, 0, g.dp.b1 );
	if ( r != EC_AD5204_ANSWER::OK ) return r;
	r = sound_dp.value_set( 1, 1, g.dp.c1 );
	if ( r != EC_AD5204_ANSWER::OK ) return r;
	r = sound_dp.value_set( 1, 2, g.dp.left);
	if ( r != EC_AD5204_ANSWER::OK ) return r;
	r = sound_dp.value_set( 1, 3, g.dp.right );
	return r;
}




static void device_power_off ( void ) {								// Отключает всю цепь питания устройства.
	ayplayer_pwr_on_pin_obj.reset();
}

static void volume_set( uint8_t left, uint8_t right) {
	sound_dp.value_set( 1, 2, left );						// Левый наушник.
	sound_dp.value_set( 1, 3, right );						// Правый.
}

// Детектирование изменения уровня громкости.
void ayplayer_button_inc_and_dec_detect ( void* param ) {
	( void )param;


}

}*/
