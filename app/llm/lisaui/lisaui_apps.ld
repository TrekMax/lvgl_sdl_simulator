SECTIONS {
    /* .lisaui_apps : {
        PROVIDE(__lisaui_apps_start = .);
        KEEP(*(.lisaui_apps))
        PROVIDE(__lisaui_apps_end = .);
    } */
    .lisaui_apps : {
        . = ALIGN(4);
        __lisaui_apps_start = .;
        KEEP (*(.lisaui*))
        . = ALIGN(4);
        __lisaui_apps_end = .;
    }
}

INSERT AFTER .data;