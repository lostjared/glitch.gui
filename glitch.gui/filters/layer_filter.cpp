#include"layer_filter.hpp"

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

    Layer012_AlphaBlend *layer012_blend = new Layer012_AlphaBlend();
    layer012_blend->setLayer(&layer1, &layer2, &layer3);
    new_filter_list.push_back({"New_Layer_012_AlphaBlend", layer012_blend});

    Layer012_AlphaBlend_Xor *layer012_blendx = new Layer012_AlphaBlend_Xor();
    layer012_blendx->setLayer(&layer1, &layer2, &layer3);
    new_filter_list.push_back({"New_Layer_012_AlphaBlend_Xor", layer012_blendx});
 
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
    new_filter_list.push_back({"New_Layer_Difference", layer_diff});

    // Diff Xor
    Layer_Difference_Xor *layer_diff_xor = new Layer_Difference_Xor();
    layer_diff_xor->setLayer(&layer1);
    new_filter_list.push_back({"New_Layer_Difference_Xor", layer_diff_xor});

}