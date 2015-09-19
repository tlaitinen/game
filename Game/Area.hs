{-# Language DeriveGeneric #-}
module Game.Area where

import GHC.Generics
import qualified Data.HashMap.Strict as HMS
import Game.Cell
import Data.Bits

type CellId  = Int
type CellPos = (Int,Int,Int)
data Area = Area {
    width  :: Int,
    height :: Int,
    floors :: Int,
    cells  :: HMS.HashMap CellId Cell
} deriving Generic

cellId :: CellPos -> CellId
cellId (x,y,z) = ((x .&. 0x3fff) `shiftL` 18) 
                  .|. ((y .&.  0x3fff) `shiftL` 4) 
                  .|. (z .&. 0xf)
                  
