/*
 *   buttons.h
 */
#ifndef __BUTTONS_H
#define __BUTTONS_H



typedef enum {
    BTN1_SHORT  = 1,
    BTN1_LONG  = 2,
} buttons_id_t;

typedef void (*buttons_notify_t)(buttons_id_t id);

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
void buttons_init(void);
void buttons_register_notify_handler(buttons_notify_t notify);
void buttons_unregister_notify_handler(void);

#endif  /* __BUTTONS_H */
