#include <stdio.h>
#include <stdlib.h>

#define SHOW_BANNER 0

static const char *parts[] = {
    "fragments/whoami.html",
    // "fragments/riscy_thoughts.html",
    // "fragments/predictions.html",
    "fragments/hummingbird.html",
    "fragments/fpgaraycaster.html",
    // "fragments/renderfellow.html",
    "fragments/other_projects.html"
};

#define LINKS \
    "        <li><a href=\"\">whoami</a></li>\n"\
    "        <li><a href=\"#riscy_thoughts\">RISC-Y Thoughts</a></li>\n"\
    "        <li><a href=\"#predictions\">Predictions</a></li>\n"\
    "        <li><a href=\"#hummingbird\">Faster Attention</a></li>\n"\
    "        <li><a href=\"#fpgaraycaster\">FPGA Raycaster</a></li>\n"\
    "        <li><a href=\"#renderfellow\">Rasterizer</a></li>\n"\
    "        <li><a href=\"#other_projects\">Other Projects</a></li>\n"\

static const size_t nparts = sizeof(parts) / sizeof(parts[0]);

int main(void) {
    FILE *out = fopen("index.html", "w");
    if (!out) {
        perror("Failed to open index.html for writing");
        return EXIT_FAILURE;
    }

    fprintf(out,
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<head>\n"
        "  <meta charset=\"UTF-8\">\n"
        "  <meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">\n"
        "  <link rel=\"icon\" href=\"images/favicon.ico\" type=\"image/x-icon\">\n"
        "  <link rel=\"icon\" type=\"image/png\" sizes=\"32x32\" href=\"favicon-32x32.png\">\n"
        "  <link rel=\"icon\" type=\"image/png\" sizes=\"16x16\" href=\"favicon-16x16.png\">\n"
        "  <link rel=\"stylesheet\" href=\"styles.css\">\n"
        "  <title>My Single-Page Site</title>\n"
        "</head>\n"
        "<body>\n"
        #if SHOW_BANNER 
            "<div class=\"top-banner\">\n"
            "I am actively seeking internship opportunities.\n"
            "</div>\n"            
        #endif
        "  <header>\n"
        "    <h1>Andres' Funky Blog</h1>\n"
        "  </header>\n"
        "  <div class=\"layout\">\n"
        "    <aside>\n"
        "      <ul>\n"
        LINKS
        "      </ul>\n"
        "    </aside>\n"
        "    <main>\n"
    );

    for (size_t i = 0; i < nparts; ++i) {
        FILE *frag = fopen(parts[i], "r");
        if (!frag) {
            fprintf(stderr, "Warning: could not open %s, skipping.\n", parts[i]);
            continue;
        }
        char buf[4096];
        while (fgets(buf, sizeof(buf), frag)) {
            fputs(buf, out);
        }
        fputs("\n", out);
        fclose(frag);
    }

    fprintf(out,
        "    </main>\n"
        "  </div>\n"
        "  <footer>&copy; 2025 Andres Torrubia. All rights reserved.</footer>\n"
        "</body>\n"
        "</html>\n"
    );

    fclose(out);
    return EXIT_SUCCESS;
}
