" 加载公共配置
source ~/.vim/scripts/mycomm.vim
" 高亮自定义关键字
syn keyword cKeywords u8 u16 u32 u64 s8 s16 s32 s64
syn keyword cKeywords U8 U16 U32 U64 S8 S16 S32 S64 typeof
hi cKeywords ctermfg=198
