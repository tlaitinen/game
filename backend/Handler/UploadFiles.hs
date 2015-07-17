{-# LANGUAGE TupleSections, OverloadedStrings #-}
module Handler.UploadFiles where

import qualified Import as I
import Import hiding (fileContentType, fileName, joinPath)
import Yesod.Auth
import Data.Time (getCurrentTime)
import qualified Data.Text as T
import Database.Persist.Sql
import qualified Settings
import System.FilePath
import System.Directory (renameFile, removeFile, doesFileExist)
import Data.Text
import System.IO
import Data.Aeson
import System.Process
import System.Exit
import Network.HTTP.Types (status500)
   

postUploadFilesR :: Handler Value
postUploadFilesR = do
    -- (Entity userId user) <- requireAuth
    (_, files) <- runRequestBody
    fi <- maybe notFound return $ lookup "file" files
    settings<- fmap appSettings getYesod
    let name = joinPath [appUploadDir settings,  
                         T.unpack (I.fileName fi)]
    liftIO $ fileMove fi name
    return $ object $ [
            "result" .= ("ok" :: Text)
        ] 

