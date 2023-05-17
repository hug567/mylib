-- show line number
vim.opt.number = true

-- require('monokai').setup { palette = require('monokai').pro }
-- require('monokai').setup { palette = require('monokai').soda }
-- require('monokai').setup { palette = require('monokai').ristretto }
require('monokai').setup {
    custom_hlgroups = {
        LineNr = {
          fg = '#bcbcbc',
        },
    }
}
