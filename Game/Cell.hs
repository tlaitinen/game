{-# LANGUAGE DeriveGeneric #-}
module Game.Cell where

import GHC.Generics
import Data.Aeson

type Walls = (Int, Int, Int, Int, Int, Int)
type Offsets = (Int, Int, Int, Int)

data Cell = Cell {
    floor      :: Int,
    background :: Int,
    walls      :: Walls,
    offsets    :: Offsets
} deriving Generic

instance FromJSON Cell
instance ToJSON Cell
