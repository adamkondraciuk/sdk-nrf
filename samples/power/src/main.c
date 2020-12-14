/*$$$LICENCE_NORDIC_STANDARD<2020>$$$*/

#include <zephyr.h>
#include <stdbool.h>
#include <stdint.h>
#include <nrfx_uarte.h>

#define UARTE(idx)                      DT_NODELABEL(uart##idx)

nrfx_uarte_config_t conf = NRFX_UARTE_DEFAULT_CONFIG(6, 8);
nrfx_uarte_t inst = NRFX_UARTE_INSTANCE(0);
static void * p_pm_uarte;

void pm_event_handler(nrfx_pm_event_t event)
{
    ;
}

void uart_handler(nrfx_uarte_event_t const * p_event, void * p_context)
{
    ;
}

int main(void)
{
    uint8_t const a[] = "before\r\n";
    uint8_t const b[] = "after\r\n";

    IRQ_CONNECT(DT_IRQN(UARTE(0)), DT_IRQ(UARTE(0), priority),
                nrfx_uarte_0_irq_handler, 0, 0);
    irq_enable(DT_IRQN(UARTE(0)));
    nrfx_uarte_init(&inst, &conf, uart_handler);

    p_pm_uarte = nrfx_uarte_pm_get(&inst);

    if (nrfx_pm_init(p_pm_uarte, pm_event_handler) != NRFX_SUCCESS)
    {
        while (1)
        {}
    }

    nrfx_uarte_tx(&inst, &a[0], sizeof(a));

    /* Wait for middle of transmission. */
    k_sleep(K_USEC(1000));

    if (nrfx_pm_power_off(p_pm_uarte, true) != NRFX_SUCCESS)
    {
        while (1)
        {}
    }

    k_sleep(K_USEC(1000000));

    if (nrfx_pm_power_on(p_pm_uarte) != NRFX_SUCCESS)
    {
        while (1)
        {}
    }

    nrfx_uarte_tx(&inst, &b[0], sizeof(b));
    while (1)
    {
        k_sleep(K_USEC(1000000));
    }
}
