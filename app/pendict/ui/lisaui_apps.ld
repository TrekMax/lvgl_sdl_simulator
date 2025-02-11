SECTIONS {
    .lisaui_apps : {
        PROVIDE(__lisaui_apps_start = .);
        KEEP(*(.lisaui_apps))
        /* KEEP(*(.lisaui_apps.*)) */
        PROVIDE(__lisaui_apps_end = .);
    }
}

INSERT AFTER .data;