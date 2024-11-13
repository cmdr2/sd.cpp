#include "stable-diffusion.h"
#include <iostream>

const int MIN_LOG_LEVEL = SD_LOG_DEBUG;
const bool COLOR_LOGGING = true;

/* Enables Printing the log level tag in color using ANSI escape codes */
void sd_log_cb(enum sd_log_level_t level, const char* log, void* data) {
    int tag_color;
    const char* level_str;
    FILE* out_stream = (level == SD_LOG_ERROR) ? stderr : stdout;

    if (!log || level < MIN_LOG_LEVEL) {
        return;
    }

    switch (level) {
        case SD_LOG_DEBUG:
            tag_color = 37;
            level_str = "DEBUG";
            break;
        case SD_LOG_INFO:
            tag_color = 34;
            level_str = "INFO";
            break;
        case SD_LOG_WARN:
            tag_color = 35;
            level_str = "WARN";
            break;
        case SD_LOG_ERROR:
            tag_color = 31;
            level_str = "ERROR";
            break;
        default: /* Potential future-proofing */
            tag_color = 33;
            level_str = "?????";
            break;
    }

    if (COLOR_LOGGING) {
        fprintf(out_stream, "\033[%d;1m[%-5s]\033[0m ", tag_color, level_str);
    } else {
        fprintf(out_stream, "[%-5s] ", level_str);
    }
    fputs(log, out_stream);
    fflush(out_stream);
}

int main(int argc, char* argv[]) {
    sd_set_log_callback(sd_log_cb, NULL);

    // Define paths for model files
    const char* model_path = "F:\\models\\stable-diffusion\\sd-v1-5.safetensors";
    // const char* model_path = "F:\\ED4\\server\\miniSD.ckpt";
    const char* clip_l_path = "";
    const char* clip_g_path = "";
    const char* t5xxl_path = "";
    const char* diffusion_model_path = "";
    const char* vae_path = "";
    const char* taesd_path = "";
    const char* control_net_path = "";
    const char* lora_model_dir = "";
    const char* embed_dir = "";
    const char* stacked_id_embed_dir = "";

    // Create the Stable Diffusion context
    sd_ctx_t* ctx = new_sd_ctx(model_path, clip_l_path, clip_g_path, t5xxl_path, diffusion_model_path,
                               vae_path, taesd_path, control_net_path, lora_model_dir,
                               embed_dir, stacked_id_embed_dir, false, false, false,
                               -1, SD_TYPE_F16, STD_DEFAULT_RNG, DEFAULT, false, false, false);

    if (ctx == NULL) {
        std::cerr << "Failed to create Stable Diffusion context." << std::endl;
        return -1;
    }

    std::cout<<"Made the context";

    // Generate image using txt2img
    const char* prompt = "A beautiful landscape painting";
    const char* negative_prompt = "";
    sd_image_t* image = txt2img(ctx, prompt, negative_prompt, 0, 7.5f, 1.0f, 512, 512,
                                EULER_A, 25, 42, 1, NULL, 0.0f, 0.0f, false, "");
                              
    if (image == NULL) {
        std::cerr << "txt2img failed." << std::endl;
        free_sd_ctx(ctx);
        return -1;
    }

    // Output image details
    std::cout << "Generated image: " << image->width << "x" << image->height << std::endl;

    return 0;
}
