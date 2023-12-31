#include"cat_vec.hpp"
#include"acidcam/ac.h"

#include<algorithm>
#include<fstream>

std::vector<std::string> cat_in_order;
std::vector<std::string> cat_sorted;

std::vector<std::string> cat_fast {
"Self AlphaBlend",
"Self Scale",
"StrobeEffect",
"Blend #3",
"Negative Paradox",
"ThoughtMode",
"Blank",
"Tri",
"Distort",
"Type",
"Color Accumlate1",
"Color Accumulate2",
"Color Accumulate3",
"Filter8",
"Filter3",
"Rainbow Blend",
"New Blend",
"Alpha Flame Filters",
"Pixel Scale",
"Median Blur",
"Diamond Pattern",
"MirrorBlend",
"Pulse",
"Sideways Mirror",
"Mirror No Blend",
"Double Vision",
"RGB Shift",
"RGB Sep",
"Graident Rainbow",
"Gradient Rainbow Flash",
"Reverse",
"Scanlines",
"TV Static",
"Mirror Average",
"Mirror Average Mix",
"Mean",
"Bitwise_XOR",
"Bitwise_AND",
"Bitwise_OR",
"Equalize",
"Reverse_XOR",
"Combine Pixels",
"FlipTrip",
"Canny",
"Boxes",
"Boxes Fade",
"Flash Black",
"Side2Side",
"Top2Bottom",
"Strobe Red Then Green Then Blue",
"Blend_Angle",
"Outward",
"Outward Square",
"ShiftPixels",
"ShiftPixelsDown",
"XorMultiBlend",
"Bitwise_Rotate",
"Bitwise_Rotate Diff",
"HPPD",
"FuzzyLines",
"GradientLines",
"GradientSelf",
"GradientSelfVertical",
"GradientDown",
"GraidentHorizontal",
"GradientRGB",
"Inter",
"UpDown",
"LeftRight",
"StrobeScan",
"BlendedScanLines",
"GradientStripes",
"WhitePixel",
"FrameBlend",
"FrameBlendRGB",
"MoveRed",
"MoveRGB",
"MoveRedGreenBlue",
"Block",
"BlockXor",
"BlockScale",
"BlockStrobe",
"PrevFrameBlend",
"Wave",
"HighWave",
"HorizontalBlend",
"VerticalBlend",
"OppositeBlend",
"HorizontalLines",
"InvertedScanlines",
"Soft_Mirror",
"KanapaTrip",
"ColorMorphing",
"ScanSwitch",
"ScanAlphaSwitch",
"NegativeStrobe",
"XorAddMul",
"BlendSwitch",
"All Red",
"All Green",
"All Blue",
"LineRGB",
"PixelRGB",
"BoxedRGB",
"KruegerSweater",
"RGBFlash",
"BlendIncrease",
"GradientReverse",
"GradientReverseVertical",
"GradientReverseBox",
"GradientNewFilter",
"ReinterpretDouble",
"ReinterpSelfScale",
"AverageLines",
"ColorRange",
"InterReverse",
"InterMirror",
"InterFullMirror",
"MirrorRGB",
"VectorIncrease",
"LineByLineReverse",
"Negate",
"DiamondStrobe",
"GridFilter8x",
"GridFilter8xBlend",
"Dual_SelfAlphaRainbow",
"SurroundPixelXor",
"Darken",
"WeakBlend",
"AverageVertical",
"AlphaBlendPosition",
"BlendRowAlpha",
"BlendRow",
"BlendRowByVar",
"BlendRowByDirection",
"BlendAlphaXor",
"SelfXorScale",
"BitwiseXorScale",
"SelfAlphaRGB",
"GradientColors",
"GradientColorsVertical",
"Bitwise_XOR_Average",
"GradientXorSelfScale",
"StrobeBlend",
"FlashWhite",
"FlashBlackAndWhite",
"SelfXorBlend",
"SelfXorDoubleFlash",
"SelfOrDoubleFlash",
"BlendRowCurvedSqrt",
"VerticalColorBars",
"GradientLeftRight",
"GraidentUpDown",
"GradientLeftRightInOut",
"GradientUpDownInOut",
"Lines",
"ColorLines",
"WhiteLines",
"ThickWhiteLines",
"FibFlash",
"ScaleFlash",
"Curtain",
"CurtainVertical",
"DarkenFilter",
"BlendInAndOut",
"BlendScaleInAndOut",
"AcidGlitch",
"XorBackwards",
"XorAlpha",
"RGBVerticalXor",
"RGBVerticalXorScale",
"RGBHorizontalXor",
"RGBHorizontalXorScale",
"FadeStrobe",
"RGBMirror",
"MirrorStrobe",
"AndStrobe",
"AndStrobeScale",
"AndPixelStrobe",
"AndOrXorStrobe",
"AndOrXorStrobeScale",
"FadeInAndOut",
"BrightStrobe",
"DarkStrobe",
"StrobeTransform",
"InitBlend",
"MoveUpLeft",
"Stuck",
"StuckStrobe",
"OrStrobe",
"DifferenceStrobe",
"BlackAndWhiteDifferenceStrobe",
"DifferenceXor",
"DifferenceBrightStrobe",
"HalfNegateStrobe",
"EveryOther",
"MirrorXor",
"MirrorXorAll",
"XorScale",
"PixelReverseXor",
"SilverBlend",
"PixelXorBlend",
"SelfAlphaScale",
"SelfScaleAlpha",
"RainbowXorBlend",
"FadeBlend",
"GammaDarken5",
"GammaDarken10",
"SelfAlphaScaleBlend",
"FadeBars",
"StrobeXor",
"InterRGB_Bars_XY",
"InterRGB_Bars_X",
"InterRGB_Bars_Y",
"FlipBlendW",
"FlipBlendWH",
"FlipBlendH",
"FlipBlendAll",
"SelfScaleXorIncrease",
"Blend_RedGreenBlue",
"XorBlend_RedGreenBlue",
"BlendIncrease_RedGreenBlue",
"Blend_RedReenBlue_Dark",
"DarkModBlend",
"PictureBuzz",
"IncDifference",
"IncDifferenceAlpha",
"Bars",
"BlendCombinedValues",
"GradientXorPixels",
"PurpleRain",
"PixelByPixelXor",
"CopyXorAlpha",
"AveragePixelsXor",
"AveragePixelAlpha",
"NegativeByRow",
"IncorrectLine",
"XorShift",
"XorWithSource",
"AlphaBlendWithSource",
"RGBSep1x",
"RGBMirror1",
"ReverseMirrorX",
"MirrorXorAll_Reverse",
"MirrorRGBReverse",
"MirrorRGBReverseBlend",
"DivideAndIncH",
"DivideAndIncW",
"IncreaseDecreaseGamma",
"GammaIncDecIncrease",
"TwistedVision",
"FlipAlphaBlend",
"NegateSwitchStrobe",
"ShuffleColorMap",
"AverageLinesBlend",
"AverageVerticalLinesBlend",
"XorSquare",
"AverageHorizontalFilter",
"AverageVerticalFilter",
"GradientAlphaXorHorizontal",
"GradientAlphaXorVertical",
"ColorTransition",
"ColorExpand",
"FlipShuffle",
"FlipOrder",
"MirrorBlendFrame",
"MirrorBlendVertical",
"BlendFor360",
"ColorXorScale",
"Bitwise_XOR_BlendFrame",
"SurroundingPixels",
"ScaleFilter",
"StrobeNegatePixel",
"StrobeNegateInOut",
"AlphaStrobeBlend",
"ChangeXorEachSecond",
"DarkNegate",
"IncreaseRGB",
"IncreaseColor",
"MaxRGB",
"IncreaseQuick",
"PixelateNoResize12",
"PixelateNoResize8",
"PixelateNoResize24",
"ReverseOnOff",
"InterlaceVerticalFilter",
"InterlaceHorizontalFilter",
"FlipFrameFilter",
"MirrorLeft",
"MirrorRight",
"MirrorBackAndForth",
"FadeFromColorToColor",
"FlipY_Axis",
"FlipX_Axis",
"FlipBoth",
"MirrorTopToBottom",
"MirrorBottomToTop",
"MirrorSwitch",
"MirrorSwitchFlip",
"MirrorLeftMirrorRightBlend",
"MirrorTopMirrorBottomBlend",
"RestoreBlack",
"AverageHorizontalDistortion",
"ColorsFilter",
"MirrorDoubleVision",
"ColorFadeFilter",
"ColorChannelMoveUpAndDown",
"AlphaBlendFlippedFilter",
"ColorVariableBlend",
"ColorXorBlend",
"ColorAddBlend",
"SelfAlphaBlendMultiThread",
"BlendChannelXor",
"ColorShiftXor",
"XorMultiply",
"Grayscale",
"MirrorLeftBottomToTop",
"MirrorRightTopToBottom",
"ColorRGB_IncDec",
"BlendWithSource25",
"BlendWithSource50",
"BlendWithSource75",
"BlendWithSource100",
"ReduceBy50",
"AlphaBlendWithSourceScale",
"ColorPositionAverageXor",
"ColorPositionXor",
"GrayStrobe",
"PositionShift",
"ShiftColorLeft",
"PreviewFilters",
"ColorPulseIncrease",
"ColorPulseAlpha",
"ColorLower75",
"LightBlend",
"ColorFadeSlow",
"Tremors",
"PulseIncreaseVariableSpeed",
"LightStrobe",
"StrobeRedChannel",
"StrobeGreenChannel",
"StrobeBlueChannel",
"PulseIncreaseFast",
"FibonacciXor",
"SelfScaleRefined",
"SelfScaleRefinedRGB",
"MirrorFadeLeftRight",
"MirrorFadeUpDown",
"DarkColors",
"Mirror_ReverseColor",
"GradientGlitch",
"GradientFilter",
"ColorOrderSwap",
"ColorOrderSwapMap",
"ColorVariableRectangles",
"VariableRectangles",
"VariableRectanglesSimple",
"MirrorSwitchMode",
"MirrorSwitchLeftRight",
"VariableRectanglesSmall",
"FrameSqueeze",
"MirrorDiamond",
"MirrorDiamondRight",
"MirrorDiamondReverse",
"MirrorDiamondBlend",
"StretchOutward",
"BlendWithColor",
"slowRed",
"slowGreen",
"slowBlue",
"ColorMapFilter",
"ReduceColors",
"ReduceColorsRed",
"ReduceColorsGreen",
"ReduceColorsBlue",
"ColorIncreaseFadeRGB",
"ColorIncreaseInOutRGB",
"FadeRtoGtoB",
"FadeRtoGtoB_Increase",
"TruncateColor",
"TruncateColor25",
"TruncateColor75",
"TruncateVariable",
"TruncateVariableSlow",
"TruncateVariableScale",
"Variable_ColorScale",
"InOut_ColorScale",
"XorRow",
"FrameJump",
"SetCurrentFrameStateAsSource",
"GradientColorBlend",
"GradientRedBlend",
"GradientGreenBlend",
"GradientBlueBlend",
"GradientColorBlendAll",
"GradientXRed",
"GradientXGreen",
"GradientXBlue",
"StretchRowMatrix8",
"GradientFlashColor",
"GradientFlashComponent",
"MirrorLeftTopToBottom",
"MirrorRightBottomToTop",
"MirrorFlipLeft",
"MirrorFlipRight",
"MirrorFlipBottomLeft",
"MirrorFlipBottomRight",
"MirrorFlipXMirrorLeft",
"MirrorFlipXMirrorRight",
"MirrorFlipYMirrorLeft",
"MirrorFlipYMirrorRight",
"MirrorFlipXLeftTopToBottom",
"MirrorFlipXLeftBottomToTop",
"MirrorFlipXRightTopToBottom",
"MirrorFlipXRightBottomToTop",
"MirrorFlipYLeftTopToBottom",
"MirrorFlipYLeftBottomToTop",
"MirrorFlipYRightTopToBottom",
"MirrorFlipYRightBottomToTop",
"HorizontalXor",
"ColorPixelDoubleXor",
"VariableLines",
"VariableLinesOffset",
"VaraibleLinesRectangle",
"VariableLinesRectangleSource",
"VariableLinesStartRectangle",
"VariableLinesStartRectangleBlend",
"VariableLinesOnOffBlend",
"VariableLinesY",
"VariableLinesY_Blend",
"VariableLinesXY_Interlaced",
"PixelateExpandDistort",
"PixelateExpandDistortX",
"PixelateExpandDistortY",
"PixelateExpandDistortExtra",
"XorScaleValue",
"ColorRowShift",
"ColorRowShiftUp",
"ColorRowShiftLeft",
"ColorRowShiftRight",
"ScanlineBlack",
"HorizontalColorOffset",
"PreviousFrameXor",
"Black",
"PrevFrameNotEqual",
"MirrorDelayLeft",
"MirrorDelayRight",
"ApplyColorRange",
"BlackLines",
"ApplyColorRangeInverted",
"ThresholdDark",
"RemoveLowRedLevel",
"RemoveLowGreenLevel",
"RemoveLowBlueLevel",
"IncreaseLowRedLevel",
"IncreaseLowGreenLevel",
"IncreaseLowBlueLevel",
"Zoom",
"OffTrackX",
"OffTrackY",
"FloatFade",
"SquareShift",
"SquareShift8",
"FloatFadeRGB",
"SquareShiftDir",
"SquareShiftExpand",
"FloatFadeVertical",
"LineTrails",
"SquareShiftDirVertical",
"StretchLineRow",
"StretchLineCol",
"StretchLineRowInc",
"StretchLineColInc",
"StretchLineRowLeftRight",
"FadeInOutBlendRGB",
"FadeInOutReverseRGB",
"SquareShiftDirRGB",
"StretchLineRowIncRGB",
"StretchLineColIncRGB",
"StretchLineRowIncSource",
"StretchLineColIncSource",
"AlternateAlpha",
"ShiftPixelsRGB",
"MirrorDiamondRGB",
"VariableLinesY_RGB",
"SquareShiftDirGradient",
"TwistedVision_RGB",
"BlendWithSourcePercent",
"LinesAcrossX",
"XorLineX",
"AlphaComponentIncrease",
"ExpandContract",
"MoveInThenMoveOut",
"MoveInThenMoveOutFast",
"DistortionFuzz",
"DistortionByRow",
"DistortionByRowRev",
"DistortionByRowVar",
"DistortionByCol",
"DistortionByColVar",
"LongLines",
"TearRight",
"TearDown",
"TearLeft",
"FadeOnOff",
"PictureStretch",
"PictureStretchPieces",
"RGBLineTrails",
"FadeRGB_Speed",
"VerticalPictureDistort",
"DiagPixelated",
"DiagPixelatedResize",
"PictureShiftDown",
"PictureShiftRight",
"FlipPictureShift",
"StretchR_Right",
"StretchG_Right",
"StretchB_Right",
"StretchR_Down",
"StretchG_Down",
"StretchB_Down",
"Diag_Line_InOut",
"XorSumStrobe",
"DetectEdges"
};

std::vector<std::string> cat_glitch {
"Square_Block_Resize",
"Square_Block_Resize_Vertical",
"Square_Block_Resize_Reset",
"Square_Block_Resize_Vert_Reset",
"Square_Block_Resize_Dir",
"Square_Block_Resize_All",
"Square_Block_Resize_Vertical_RGB",
"Square_Block_Resize_RGB",
"DiagPixel",
"DiagPixelY",
"DiagPixelY2",
"DiagPixelY3",
"DiagPixelY4",
"DiagSquare",
"DiagSquareLarge",
"DiagonalSquareCollection",
"DiagnoalSquareSize",
"DiagonalSquareSizeOnOff",
"DiagSquare8",
"DiagSquareX",
"DiagInward",
"DiagSquareInward",
"DiagSquareInwardResize",
"DiagSquareInwardResizeXY",
"DiagPixelated",
"SquareShift",
"SquareShift8",
"SquareShiftDir",
"SquareShiftExpand",
"SquareShiftDirVertical",
"SquareShiftDirGradient",
"VariableRectanglesSimple",
"VariableRectanglesExtra",
"VariableRectanglesSmall",
"VariableRectanglesLarge",
"LineInLineOut",
"LineInLineOut_Increase",
"LineInLineOut2_Increase",
"LineInLineOut3_Increase",
"LineInLineOut4_Increase",
"LineInLineOut_Vertical",
"LineInLineOut_VerticalIncrease",
"FrameSep",
"FrameSep2",
"DefStutter",
"StutterFilter",
"FrameOffsetRSize",
"FrameOffsetRSize2",
"FrameOffsetRSize3",
"FrameOffsetRSize4",
"SqOnOff",
"SqOnOffAlpha",
"SqOnOffAlphaClip",
"SqOnOffAlphaClipFast",
"SqOnOffAlphaPixel",
"SqOnOffDiff",
"SqOnOffSize",
"Placement",
"FrameSep3",
"FrameSep4",
"FrameSep5",
"FrameSepDiff",
"FrameSepResize",
"FrameSepResize2",
"FrameSepSquare",
"FrameSepH",
"FrameSkip",
"FrameSkipResize"
};

std::vector<std::string> cat_mirror {
"MirrorBlend",
"Sideways Mirror",
"Mirror No Blend",
"Mirror Average",
"Mirror Average Mix",
"Soft_Mirror",
"InterMirror",
"InterFullMirror",
"MirrorRGB",
"RGBMirror",
"MirrorStrobe",
"MirrorXor",
"MirrorXorAll",
"MirrorXorScale",
"EnergyMirror",
"MirrorXorAlpha",
"BlurredMirror",
"MirrorMedianBlend",
"FlipMirror",
"FlipMirrorAverage",
"RGBMirror1",
"RGBMirror1Median",
"FlashMirror",
"ReverseMirrorX",
"MirrorXorAll_Reverse",
"MirrorRGBReverse",
"MirrorRGBReverseBlend",
"MirrorBitwiseXor",
"BlurMirrorGamma",
"EnergyMirrorDark",
"AlphaBlendMirror",
"TwistedMirror",
"MirrorMedian",
"MirrorMatrixCollection",
"MirrorMatrixSource",
"SmoothMirrorBlurFlip",
"MirrorOrder",
"BlurMirrorOrder",
"AveragePixelMirror",
"MirrorOrderAlpha",
"MirrorAlphaBlend",
"MirrorBlendFrame",
"MirrorBlendVertical",
"MirrorVerticalAndHorizontal",
"MirrorSidesMedian",
"MirrorEachSecond",
"Mirror_Xor_Combined",
"MirrorFrameShuffle",
"MirrorShuffleSmooth",
"Mirror_Xor_Smooth",
"XorMirrorBlendFrame",
"MatrixCollectionMirrorDirection",
"SplitFrameMirror",
"MirrorLeft",
"MirrorRight",
"MirrorBackAndForth",
"FlipMirrorAlphaBlend",
"StretchVerticalMirror",
"MirrorTopToBottom",
"MirrorBottomToTop",
"MirrorSwitch",
"MirrorSwitchFlip",
"MirrorLeftMirrorRightBlend",
"MirrorTopMirrorBottomBlend",
"MirrorAll",
"MirrorDoubleVision",
"Mirror_Rainbow_Blur",
"MirrorMedianBlur",
"MirrorLeftBottomToTop",
"MirrorRightTopToBottom",
"AlphaBlendMirrorChannelSort",
"GhostMirrorReversed",
"GhostMirrorFade",
"MirrorFadeLeftRight",
"MirrorFadeUpDown",
"MirrorFadeAll",
"AlphaBlendMirrorFade",
"Mirror_ReverseColor",
"MirrorSwitchMode",
"MirrorSwitchLeftRight",
"MatrixCollectionFramesMirrorLeft",
"MirrorDiamond",
"MirrorDiamondRight",
"MirrorDiamondReverse",
"MirrorDiamondBlend",
"MedianMirrorAllBlend",
"MirrorTrailsLeft",
"MirrorTrailsLeftRightTopBottom",
"MirrorTrailsRightLeftBottomTop",
"MirrorTrailsFlash",
"MirrorLeftTopToBottom",
"MirrorRightBottomToTop",
"MirrorFlipLeft",
"MirrorFlipRight",
"MirrorFlipBottomLeft",
"MirrorFlipBottomRight",
"MirrorFlipXMirrorLeft",
"MirrorFlipXMirrorRight",
"MirrorFlipYMirrorLeft",
"MirrorFlipYMirrorRight",
"MirrorFlipXLeftTopToBottom",
"MirrorFlipXLeftBottomToTop",
"MirrorFlipXRightTopToBottom",
"MirrorFlipXRightBottomToTop",
"MirrorFlipYLeftTopToBottom",
"MirrorFlipYLeftBottomToTop",
"MirrorFlipYRightTopToBottom",
"MirrorFlipYRightBottomToTop",
"MirrorFadeDelay",
"MirrorDelayLeft",
"MirrorDelayRight",
"MirrorDiamondRGB"
};

std::vector<std::string> *vec_cat[] = { &cat_in_order, &cat_sorted, &cat_fast, &cat_glitch, &cat_mirror, 0 };
std::vector<custom_filter> cat_custom;
std::unordered_map<std::string, int> cat_custom_index;

void load_custom() {
    std::fstream file;
    file.open("custom.dat", std::ios::in);
    if(!file.is_open()) {
        std::cerr << "Error opening custom file: custom.dat\n";
        return;
    }
    while(!file.eof()) {
        std::string line;
        std::getline(file, line);
        if(file) {
            std::string name;
            auto pos = line.find("=");
            if(pos == std::string::npos) break;
            name = line.substr(0, pos);
            line = line.substr(pos+1, line.length());
            std::vector<std::string> names;
            while(line.find(",") != std::string::npos) {
                std::string name1;
                auto pos = line.find(",");
                name1 = line.substr(0, pos);
                line = line.substr(pos+1, line.length());
                names.push_back(name1);
            }
            names.push_back(line);
            cat_custom.push_back(std::make_pair(name, names));
        }
    }
    file.close();
    custom_setup_map(true);
}

void custom_setup_map(bool clear) {

   if(clear && !cat_custom_index.empty()) {
        cat_custom_index.erase(cat_custom_index.begin(), cat_custom_index.end());
    }

     for(size_t i = 0; i < cat_custom.size(); ++i) {
        cat_custom_index[cat_custom[i].first] = i;
    }
}

void save_custom() {
    std::fstream file;
    file.open("custom.dat", std::ios::out);
    if(!file.is_open()) {
        std::cerr << "Error saving custom file: custom.dat\n";
        return;
    }

    for(size_t i = 0; i < cat_custom.size(); ++i) {
        std::string &name = cat_custom[i].first;
        file << name << "=";
        for(size_t z = 0; z < cat_custom[i].second.size()-1; ++z) {
           std::string &name = cat_custom[i].second[z];
           file << name << ",";
        }
        file << cat_custom[i].second[cat_custom[i].second.size()-1] << "\n";
      }

    file.close();
}

void build_lists() {
    for(auto it = ac::solo_filter.begin(); it != ac::solo_filter.end(); ++it) {
        cat_in_order.push_back(*it);
        cat_sorted.push_back(*it);
    }
    std::sort(cat_sorted.begin(), cat_sorted.end());
    load_custom();
}

bool custom_exists(const std::string &s) {
    auto pos = cat_custom_index.find(s);
    if(pos == cat_custom_index.end())
        return false;
    return true;
}