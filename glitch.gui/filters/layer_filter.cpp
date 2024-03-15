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

    Layer_012_Index *l_1 = new Layer_012_Index();
    l_1->setLayers(&layer1, &layer2, &layer3);
    l_1->setMode(0);
    new_filter_list.push_back({"New_Layer_012_Increment", l_1});

    Layer_012_Index *l_2 = new Layer_012_Index();
    l_2->setLayers(&layer1, &layer2, &layer3);
    l_2->setMode(1);
    new_filter_list.push_back({"New_Layer_012_Shuffle", l_2});
       
    Layer_012_Index *l_3 = new Layer_012_Index();
    l_3->setLayers(&layer1, &layer2, &layer3);
    l_3->setMode(2);
    new_filter_list.push_back({"New_Layer_012_Random", l_3});

    New_MedianBlend3 *mb3 = new New_MedianBlend3();
    mb3->setLayers(&layer1, &layer2, &layer3);
    new_filter_list.push_back({"New_Layer_012_MedianBlend3", mb3});

    // concat variations
    Layer_012_AlphaBlendConcat *l_1c = new Layer_012_AlphaBlendConcat();
    l_1c->setLayers(&layer1, &layer2, &layer3);
    new_filter_list.push_back({"New_Layer_012_AlphaBlendConcat", l_1c});

    Layer_012_AlphaBlendConcat *l_1c2 = new Layer_012_AlphaBlendConcat();
    l_1c2->setLayers(&layer1, &layer2, &layer3);
    l_1c2->setRandomDir(true);
    new_filter_list.push_back({"New_Layer_012_AlphaBlendConcatDir", l_1c2});

    Layer_012_AlphaBlendConcat *l_1c3 = new Layer_012_AlphaBlendConcat();
    l_1c3->setLayers(&layer1, &layer2, &layer3);
    l_1c3->setRandomDir(true);
    l_1c3->setOverflow(true);
    new_filter_list.push_back({"New_Layer_012_AlphaBlendConcatCap", l_1c3});

    Layer_012_AlphaBlendConcat *l_1c4 = new Layer_012_AlphaBlendConcat();
    l_1c4->setLayers(&layer1, &layer2, &layer3);
    l_1c4->setRandomDir(true);
    l_1c4->setRandomNot(true);
    new_filter_list.push_back({"New_Layer_012_AlphaBlendConcatNot", l_1c4});
    // end variations

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
    new_filter_list.push_back({"New_Layer_0_DualAlphaDir", layer_dir});

    Layer_0_EdgeFilter *l_ed = new  Layer_0_EdgeFilter();
    l_ed->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_EdgeFilter", l_ed});

    Layer_0_GlitchBleed *l_gb = new Layer_0_GlitchBleed();
    l_gb->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_0_GlitchBleed", l_gb});

    Layer_0_Swap *l_swap = new Layer_0_Swap();
    l_swap->setLayer(&layer1);

    new_filter_list.push_back({"New_Layer_0_Swap", l_swap});

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

    MedianNoiseReduction *m_n = new MedianNoiseReduction();
    new_filter_list.push_back({"New_MedianNoiseReduction", m_n});

    BilateralNoiseReduction *b_n = new  BilateralNoiseReduction();
    new_filter_list.push_back({"New_BilateralNoiseReduction", b_n});

    BlackEdgeFilter *b_e_f = new BlackEdgeFilter();
    new_filter_list.push_back({"New_BlackEdgeFilter", b_e_f});

    AlphaRandom *al_r = new AlphaRandom();
    new_filter_list.push_back({"New_AlphaRandom", al_r});

    New_MedianBlend *n_med = new New_MedianBlend ();
    new_filter_list.push_back({"New_MedianBlend", n_med});  

    New_ColorScale *n_cxor = new New_ColorScale();
    new_filter_list.push_back({"New_ColorScale", n_cxor}); 

    ColorGradientShift *c_shift30 = new ColorGradientShift(30);
    new_filter_list.push_back({"New_ColorGradientShift30", c_shift30});
    
    ColorGradientShift *c_shift60 = new ColorGradientShift(60);
    new_filter_list.push_back({"New_ColorGradientShift60", c_shift60});

    GradientBoxes *grad_box30 = new GradientBoxes (3, 3, 30.0f);
    new_filter_list.push_back({"New_GradientBoxes30", grad_box30});

    GradientBoxes *grad_box60 = new GradientBoxes (3, 3, 60.0f);
    new_filter_list.push_back({"New_GradientBoxes60", grad_box60});

    FrameStoreSmash *smash = new FrameStoreSmash(4);
    new_filter_list.push_back({"New_Very_Slow_FrameSmash", smash});

    Flash *flash = new Flash();
    new_filter_list.push_back({"New_Better_Random_Strobe", flash});

    PencilSketchFilter *pencil = new PencilSketchFilter();
    new_filter_list.push_back({"New_Pencil_Sketch", pencil});

    OldPhotograph *old_p = new OldPhotograph();
    new_filter_list.push_back({"New_Old_Photograph", old_p});

    FishEyeLens *fish_eye = new FishEyeLens(0.01);
    new_filter_list.push_back({"New_FishEye_Lens", fish_eye});

    FishEyeLens *fish_eye_s = new FishEyeLens(0.001);
    new_filter_list.push_back({"New_FishEye_Lens_Slow", fish_eye_s});

    FishEyeLens *fish_eye_f = new FishEyeLens(0.5);
    fish_eye_f->setFixed(0.5);
    new_filter_list.push_back({"New_FishEye_Lens_Fixed", fish_eye_f});
 
    FunhouseMirror *fun_mirror_h = new FunhouseMirror();
    fun_mirror_h->setEffect(0);
    new_filter_list.push_back({"New_FunhouseMirror_Horizontal", fun_mirror_h});

    FunhouseMirror *fun_mirror_v = new FunhouseMirror();
    fun_mirror_v->setEffect(1);
    new_filter_list.push_back({"New_FunhouseMirror_Vertical", fun_mirror_v});

   FunhouseMirror *fun_mirror_h1 = new FunhouseMirror();
    fun_mirror_h1->setEffect(0);
    fun_mirror_h1->setSpeed(0.001);
    new_filter_list.push_back({"New_FunhouseMirror_Horizontal_Slow", fun_mirror_h1});

    FunhouseMirror *fun_mirror_v1 = new FunhouseMirror();
    fun_mirror_v1->setEffect(1);
    fun_mirror_v1->setSpeed(0.001);
    new_filter_list.push_back({"New_FunhouseMirror_Vertical_Slow", fun_mirror_v1});


    FunhouseMirror *fun_mirror_h2 = new FunhouseMirror();
    fun_mirror_h2->setEffect(0);
    fun_mirror_h2->setGrowType(0);
    new_filter_list.push_back({"New_FunhouseMirror_Horizontal_Grow", fun_mirror_h2});

    FunhouseMirror *fun_mirror_v2 = new FunhouseMirror();
    fun_mirror_v2->setEffect(1);
    fun_mirror_v2->setGrowType(1);
    new_filter_list.push_back({"New_FunhouseMirror_Vertical_Grow", fun_mirror_v2});
    
    RGB_Shift *rgb_s = new RGB_Shift ();
    new_filter_list.push_back({"New_RGB_Shift", rgb_s});

    CropEdges *crop_e = new CropEdges();
    new_filter_list.push_back({"New_CropEdges", crop_e});

    Fractal *frac = new Fractal();
    new_filter_list.push_back({"New_SuperSlow_Fractal", frac});

    Fractal *frac_r = new Fractal();
    frac_r->resize(true);
    new_filter_list.push_back({"New_Low_Fractal", frac_r});  

    PopArt *pop = new PopArt();
    new_filter_list.push_back({"New_PopArt", pop});

    PopArt *pop1 = new PopArt(3.0, 128);
    new_filter_list.push_back({"New_PopArt_Strong", pop1});

    SlitScan *scan1 = new SlitScan();
    new_filter_list.push_back({"New_SlitScan_640", scan1});
    SlitScan *scan2 = new SlitScan(2, 1280, 720);
    new_filter_list.push_back({"New_SlitScan_1280", scan2});

    Ripple *rip = new Ripple();
    new_filter_list.push_back({"New_Ripple", rip});

    VanGoghEffect *vge = new VanGoghEffect();
    new_filter_list.push_back({"New_VanGoghEffect", vge});

    PixelSort_RGB *p_rgb = new PixelSort_RGB();
    new_filter_list.push_back({"New_PixelSort_RGB", p_rgb});

    KaleidoscopeEffect *kale = new KaleidoscopeEffect();
    new_filter_list.push_back({"New_Kaleidoscope", kale});

   TwirlEffect *twirl_e = new TwirlEffect();
    new_filter_list.push_back({"New_TwirlEffect", twirl_e});

    InfiniteZoom *inf_z = new InfiniteZoom();
    new_filter_list.push_back({"New_Infinite_Zoom", inf_z});

    CrystalBallEffect *cball = new CrystalBallEffect(0.5f, cv::Point2f(-1, -1), false);
    new_filter_list.push_back({"New_CrystalBall_Effect", cball});

    CrystalBallEffect *cball_i = new CrystalBallEffect(0.5f, cv::Point2f(-1, -1), true);
    new_filter_list.push_back({"New_CrystalBall_Increase_Effect", cball_i});

    CrystalBallEffect *cball_f = new CrystalBallEffect(1.0f, cv::Point2f(-1, -1), false);
    new_filter_list.push_back({"New_CrystalBall_Fixed_Effect", cball_f});

    StretchSqueezeEffect *stretch_s = new  StretchSqueezeEffect();
    new_filter_list.push_back({"New_Stretch_Squeeze", stretch_s});

    MirrorBallEffect *mirror_b = new MirrorBallEffect();
    new_filter_list.push_back({"New_MirrorBall", mirror_b});

    MorphologicalWarpEffect *warp_e = new MorphologicalWarpEffect();
    new_filter_list.push_back({"New_MorphologicalWarp", warp_e});
    

    InfraredEffect *infra_red = new InfraredEffect();
    new_filter_list.push_back({"New_Infrared", infra_red});    

    RGB_Real_Increase *r_real = new RGB_Real_Increase();
    new_filter_list.push_back({"New_Real_Inc", r_real});

    ColorMap *color_map_autumn = new ColorMap(0);
    new_filter_list.push_back({"New_ColorMap_AUTUMN", color_map_autumn});

    ColorMap *color_map_bone = new ColorMap(1);
    new_filter_list.push_back({"New_ColorMap_BONE", color_map_bone});

    ColorMap *color_map_jet = new ColorMap(2);
    new_filter_list.push_back({"New_ColorMap_JET", color_map_jet});

    ColorMap *color_map_winter = new ColorMap(3);
    new_filter_list.push_back({"New_ColorMap_WINTER", color_map_winter});

    ColorMap *color_map_rainbow = new ColorMap(4);
    new_filter_list.push_back({"New_ColorMap_RAINBOW", color_map_rainbow});

    ColorMap *color_map_ocean = new ColorMap(5);
    new_filter_list.push_back({"New_ColorMap_OCEAN", color_map_ocean});

    ColorMap *color_map_summer = new ColorMap(6);
    new_filter_list.push_back({"New_ColorMap_SUMMER", color_map_summer});

    ColorMap *color_map_spring = new ColorMap(7);
    new_filter_list.push_back({"New_ColorMap_SPRING", color_map_spring});

    ColorMap *color_map_cool = new ColorMap(8);
    new_filter_list.push_back({"New_ColorMap_COOL", color_map_cool});

    ColorMap *color_map_hsv = new ColorMap(9);
    new_filter_list.push_back({"New_ColorMap_HSV", color_map_hsv});

    ColorMap *color_map_pink = new ColorMap(10);
    new_filter_list.push_back({"New_ColorMap_PINK", color_map_pink});

    ColorMap *color_map_hot = new ColorMap(11);
    new_filter_list.push_back({"New_ColorMap_HOT", color_map_hot});

    ColorMap *color_map_parula = new ColorMap(12);
    new_filter_list.push_back({"New_ColorMap_PARULA", color_map_parula});
#ifndef _WIN32
    ColorMap *color_map_magma = new ColorMap(13);
    new_filter_list.push_back({"New_ColorMap_MAGMA", color_map_magma});

    ColorMap *color_map_inferno = new ColorMap(14);
    new_filter_list.push_back({"New_ColorMap_INFERNO", color_map_inferno});

    ColorMap *color_map_plasma = new ColorMap(15);
    new_filter_list.push_back({"New_ColorMap_PLASMA", color_map_plasma});

    ColorMap *color_map_viridis = new ColorMap(16);
    new_filter_list.push_back({"New_ColorMap_VIRIDIS", color_map_viridis});

    ColorMap *color_map_cividis = new ColorMap(17);
    new_filter_list.push_back({"New_ColorMap_CIVIDIS", color_map_cividis});
    
    ColorMap *color_map_twilight = new ColorMap(18);
    new_filter_list.push_back({"New_ColorMap_TWILIGHT", color_map_twilight});

    ColorMap *color_map_twilight_shifted = new ColorMap(19);
    new_filter_list.push_back({"New_ColorMap_TWILIGHT_SHIFTED", color_map_twilight_shifted});

    ColorMap *color_map_turbo = new ColorMap(20);
    new_filter_list.push_back({"New_ColorMap_TURBO", color_map_turbo});
#endif
}
