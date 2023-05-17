-- Update plugin: :PackerSync
return require('packer').startup(function()
  -- plugin management, Packer can manage itself
  use 'wbthomason/packer.nvim'

  -- directory tree
  -- Unless you are still migrating, remove the deprecated commands from v1.x
  vim.cmd([[ let g:neo_tree_remove_legacy_commands = 1 ]])
  use {
    "nvim-neo-tree/neo-tree.nvim",
      branch = "v2.x",
      requires = {
        "nvim-lua/plenary.nvim",
        "nvim-tree/nvim-web-devicons", -- not strictly required, but recommended
        "MunifTanjim/nui.nvim",
      }
    }

  -- color theme
  use 'tanvirtin/monokai.nvim'
end)
