{-# Language DeriveGeneric #-}
{-# Language FlexibleInstances #-}
{-# Language OverloadedStrings #-}
module Game.Area where

import GHC.Generics
import qualified Data.HashMap.Strict as HMS
import Game.Cell
import Data.Bits
import Data.Text (Text)
import qualified Data.Text as T
import Data.Aeson
import Data.Maybe
import qualified Data.Text.Read as DTR

type CellId  = Int
type CellPos = (Int,Int,Int)
data Area = Area {
    width  :: Int,
    height :: Int,
    floors :: Int,
    cells  :: HMS.HashMap CellId Cell
} deriving Generic

instance ToJSON Area
instance FromJSON Area
instance FromJSON (HMS.HashMap CellId Cell) where
    parseJSON v = do
        x <- parseJSON v
        return $ HMS.fromList $ mapMaybe f $ HMS.toList (x :: HMS.HashMap Text Cell)
        where
            f (k,y) = case DTR.decimal k of
                Right (k',"") -> Just (k',y)
                _ -> Nothing
        
            
instance ToJSON (HMS.HashMap CellId Cell) where
    toJSON cs = Object $ HMS.fromList [ (T.pack $ show k, toJSON v) | (k,v) <- HMS.toList cs ]

cellId :: CellPos -> CellId
cellId (x,y,z) = ((x .&. 0x3fff) `shiftL` 18) 
                  .|. ((y .&.  0x3fff) `shiftL` 4) 
                  .|. (z .&. 0xf)

                 
