{-# LANGUAGE DeriveGeneric #-}
module Game.Cell where

import GHC.Generics
import Data.Int

type Walls = (Int, Int, Int, Int, Int, Int)
type Offsets = (Int, Int, Int, Int)

data Cell = Cell {
    floor      :: Int,
    background :: Int,
    walls      :: Walls,
    offsets    :: Offsets
} deriving Generic
