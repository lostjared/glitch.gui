#include"layer_filter.hpp"
// all these pointers are released on clean up
// see: release_filter_list() called on MainWindow destructor 
void add_layer_filters(Layer &layer1, Layer &layer2, Layer &layer3) {
  // 0

    Layer_AlphaBlend25 *layer0_blend25 = new Layer_AlphaBlend25();
    layer0_blend25->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_AlphaBlend25", layer0_blend25});

    Layer_AlphaBlend50 *layer0_blend50 = new Layer_AlphaBlend50();
    layer0_blend50->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_AlphaBlend50", layer0_blend50});

    Layer_AlphaBlend75 *layer0_blend75 = new Layer_AlphaBlend75();
    layer0_blend75->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_AlphaBlend75", layer0_blend75});

    // 1

    Layer_AlphaBlend25 *layer1_blend25 = new Layer_AlphaBlend25();
    layer1_blend25->setLayer(&layer2);
    new_filter_list.push_back({"New_Layer_1_AlphaBlend25", layer1_blend25});

    Layer_AlphaBlend50 *layer1_blend50 = new Layer_AlphaBlend50();
    layer1_blend50->setLayer(&layer2);
    new_filter_list.push_back({"New_Layer_1_AlphaBlend50", layer1_blend50});

    Layer_AlphaBlend75 *layer1_blend75 = new Layer_AlphaBlend75();
    layer1_blend75->setLayer(&layer2);
    new_filter_list.push_back({"New_Layer_1_AlphaBlend75", layer1_blend75});

    // 2

    Layer_AlphaBlend25 *layer2_blend25 = new Layer_AlphaBlend25();
    layer2_blend25->setLayer(&layer3);
    new_filter_list.push_back({"New_Layer_2_AlphaBlend25", layer2_blend25});

    Layer_AlphaBlend50 *layer2_blend50 = new Layer_AlphaBlend50();
    layer2_blend50->setLayer(&layer3);
    new_filter_list.push_back({"New_Layer_2_AlphaBlend50", layer2_blend50});

    Layer_AlphaBlend75 *layer2_blend75 = new Layer_AlphaBlend75();
    layer2_blend75->setLayer(&layer3);
    new_filter_list.push_back({"New_Layer_2_AlphaBlend75", layer2_blend75});

    Layer_0_Intertwine *layer_inter = new Layer_0_Intertwine();
    layer_inter->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_Intertwine", layer_inter});

    Layer012_AlphaBlend *layer012_blend = new Layer012_AlphaBlend();
    layer012_blend->setLayer(&layer1, &layer2, &layer3);
    new_filter_list.push_back({"New_Layer_012_AlphaBlend", layer012_blend});

    Layer012_AlphaBlend_Xor *layer012_blendx = new Layer012_AlphaBlend_Xor();
    layer012_blendx->setLayer(&layer1, &layer2, &layer3);
    new_filter_list.push_back({"New_Layer_012_AlphaBlend_Xor", layer012_blendx});

    Layer012_ChannelMerge *layer012_merge = new Layer012_ChannelMerge();
    layer012_merge->setLayer(&layer1, &layer2, &layer3);
    new_filter_list.push_back({"New_Layer_012_ChannelMerge", layer012_merge});

    Layer012_SlideShow *layer012_s = new Layer012_SlideShow();
    layer012_s->setLayer(&layer1, &layer2, &layer3);
    new_filter_list.push_back({"New_Layer_012_SlideShow", layer012_s});
 
    // Fade
    Layer_AlphaBlendFade01 *layer01_fade = new Layer_AlphaBlendFade01();
    layer01_fade->setLayer(&layer1, &layer2);
    new_filter_list.push_back({"New_Layer_01_Fade", layer01_fade});

    // FadeXOR
    Layer_AlphaBlendFade01 *layer01_fade_xor = new Layer_AlphaBlendFade01();
    layer01_fade_xor->setXor(true);
    layer01_fade_xor->setLayer(&layer1,&layer2);
    new_filter_list.push_back({"New_Layer_01_Fade_Xor", layer01_fade_xor});

    // Diff
    Layer_Difference *layer_diff = new Layer_Difference();
    layer_diff->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_Difference", layer_diff});

    // Diff Xor
    Layer_Difference_Xor *layer_diff_xor = new Layer_Difference_Xor();
    layer_diff_xor->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_Difference_Xor", layer_diff_xor});

    //Variable Diff    
    Layer_Variable_Diff *layer_var_diff = new  Layer_Variable_Diff();
    layer_var_diff->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_Variable_Diff", layer_var_diff});

    Layer_Matrix_Diff  *layer_matrix = new Layer_Matrix_Diff();
    layer_matrix->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_Matrix_Diff", layer_matrix});

    Layer_Matrix_Color *layer_mc = new Layer_Matrix_Color();
    layer_mc->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_Matrix_Color", layer_mc});

    Layer0_Wave *wave = new Layer0_Wave();
    wave->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_Wave", wave});
    
    Layer0_XorWave *wavex = new Layer0_XorWave();
    wavex->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_XorWave", wavex});
    
    Layer_Fill_NotZero *nz_fill = new Layer_Fill_NotZero();
    nz_fill->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_Fill_NotZero", nz_fill});

    Layer_Fill_Zero *z_fill = new Layer_Fill_Zero();
    z_fill->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_Fill_Zero", z_fill});

    ThreshEffect_Layer *t_l = new ThreshEffect_Layer ();
    t_l->initLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_Threshold_Rand", t_l});

    BackgroundReplacementEffect *bg_rx = new BackgroundReplacementEffect();
    bg_rx->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_GreenScreen", bg_rx});

    Layer_0_DualAlphaScale *l0_b = new Layer_0_DualAlphaScale();
    l0_b->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_DualAlphaScale", l0_b});

    Layer_0_DualAlphaBlend *layer_d = new Layer_0_DualAlphaBlend();
    layer_d->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_DualAlphaBlend", layer_d});

    Layer_0_DualAlphaDir *layer_dir = new Layer_0_DualAlphaDir();
    layer_dir->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_DUalAlphaDir", layer_dir});

    // Other 
    Light_Increase *light_inc = new Light_Increase();
    new_filter_list.push_back({"New_Light_Increase", light_inc});

    Light_Echo *light_echo = new Light_Echo();
    new_filter_list.push_back({"New_Light_Echo", light_echo});

    Light_Wrap *light_wrap = new Light_Wrap();
    new_filter_list.push_back({"New_Light_Wrap", light_wrap});

    MedianBlend_Low *m_low = new  MedianBlend_Low();
    new_filter_list.push_back({"New_Low_MedianBlend", m_low});

    MetalBlend_Low *m_mt_low = new  MetalBlend_Low();
    new_filter_list.push_back({"New_Low_MetalBlend", m_mt_low});

    StandardDef *std_def = new StandardDef();
    new_filter_list.push_back({"New_Standad_Def", std_def});

    ScalingDef *sc_def = new ScalingDef();
    new_filter_list.push_back({"New_Scaling_Def", sc_def});

    AlphaSin *asin = new AlphaSin();
    new_filter_list.push_back({"New_AlphaSin", asin});
    
    LFOWave *l_wav = new LFOWave();
    new_filter_list.push_back({"New_LFOWave", l_wav});

    Wave_Freq *f_wav = new Wave_Freq();
    new_filter_list.push_back({"New_Wave_Freq", f_wav});

    Scrambler *scr = new Scrambler();
    new_filter_list.push_back({"New_Scrambler", scr});

    GradientLFO *g_l = new GradientLFO();
    new_filter_list.push_back({"New_GradientLFO", g_l});

    AlphaKnobs *a_k = new AlphaKnobs();
    new_filter_list.push_back({"New_Alpha_Knobs", a_k});

    DynamicGradientOverlay *dg = new DynamicGradientOverlay();
    new_filter_list.push_back({"New_DynamicGradientOverlay", dg});

    ThreshEffect *t_e = new ThreshEffect();
    new_filter_list.push_back({"New_ThreshEffect", t_e});

    CartoonEffect *car = new CartoonEffect();
    new_filter_list.push_back({"New_Slow_CartoonEffect", car});
    
    FilmGrain *film_g = new FilmGrain();
    new_filter_list.push_back({"New_Slow_Film_Grain", film_g});

    WaterColor *wc = new WaterColor();
    new_filter_list.push_back({"New_Soft_WaterColor", wc});

}