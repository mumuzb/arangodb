////////////////////////////////////////////////////////////////////////////////
/// @brief arango server
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2004-2012 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Dr. Frank Celler
/// @author Copyright 2011-2012, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIAGENS_REST_SERVER_ARANGO_SERVER_H
#define TRIAGENS_REST_SERVER_ARANGO_SERVER_H 1

#ifdef _WIN32
  #include "BasicsC/win-utils.h"
#endif

#include "Rest/AnyServer.h"
#include "Rest/OperationMode.h"

#include "VocBase/vocbase.h"

// -----------------------------------------------------------------------------
// --SECTION--                                              forward declarations
// -----------------------------------------------------------------------------

namespace triagens {
  namespace rest {
    class ApplicationDispatcher;
    class ApplicationEndpointServer;
    class ApplicationScheduler;
    class HttpServer;
    class HttpsServer;
  }

  namespace admin {
    class ApplicationAdminServer;
  }

  namespace arango {
    class ApplicationMR;
    class ApplicationV8;

// -----------------------------------------------------------------------------
// --SECTION--                                                class ArangoServer
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief ArangoDB server
////////////////////////////////////////////////////////////////////////////////

  class ArangoServer : public rest::AnyServer {
      private:
        ArangoServer (const ArangoServer&);
        ArangoServer& operator= (const ArangoServer&);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                      constructors and destructors
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

      public:

////////////////////////////////////////////////////////////////////////////////
/// @brief constructor
////////////////////////////////////////////////////////////////////////////////

        ArangoServer (int argc, char** argv);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                 AnyServer methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

      public:

////////////////////////////////////////////////////////////////////////////////
/// {@inheritDoc}
////////////////////////////////////////////////////////////////////////////////

        void buildApplicationServer ();

////////////////////////////////////////////////////////////////////////////////
/// {@inheritDoc}
////////////////////////////////////////////////////////////////////////////////

        int startupServer ();

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                             public static methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

      public:

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                   private methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

      private:

////////////////////////////////////////////////////////////////////////////////
/// @brief executes the JavaScript emergency console
////////////////////////////////////////////////////////////////////////////////

        int executeConsole (triagens::rest::OperationMode::server_operation_mode_e);

////////////////////////////////////////////////////////////////////////////////
/// @brief executes the ruby emergency console
////////////////////////////////////////////////////////////////////////////////

#ifdef TRI_ENABLE_MRUBY
        int executeRubyConsole ();
#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief opens the database
////////////////////////////////////////////////////////////////////////////////

        void openDatabase ();

////////////////////////////////////////////////////////////////////////////////
/// @brief closes the database
////////////////////////////////////////////////////////////////////////////////

        void closeDatabase ();

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                 private variables
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ArangoDB
/// @{
////////////////////////////////////////////////////////////////////////////////

      private:
        
////////////////////////////////////////////////////////////////////////////////
/// @brief number of command line arguments
////////////////////////////////////////////////////////////////////////////////

        int _argc;

////////////////////////////////////////////////////////////////////////////////
/// @brief command line arguments
////////////////////////////////////////////////////////////////////////////////

        char** _argv;

////////////////////////////////////////////////////////////////////////////////
/// @brief path to binary
////////////////////////////////////////////////////////////////////////////////

        std::string _binaryPath;

////////////////////////////////////////////////////////////////////////////////
/// @brief application scheduler
////////////////////////////////////////////////////////////////////////////////

        rest::ApplicationScheduler* _applicationScheduler;

////////////////////////////////////////////////////////////////////////////////
/// @brief application dispatcher
////////////////////////////////////////////////////////////////////////////////

        rest::ApplicationDispatcher* _applicationDispatcher;

////////////////////////////////////////////////////////////////////////////////
/// @brief application endpoint server
////////////////////////////////////////////////////////////////////////////////

        rest::ApplicationEndpointServer* _applicationEndpointServer;

////////////////////////////////////////////////////////////////////////////////
/// @brief constructed admin server application
////////////////////////////////////////////////////////////////////////////////

        admin::ApplicationAdminServer* _applicationAdminServer;

////////////////////////////////////////////////////////////////////////////////
/// @brief application MR
////////////////////////////////////////////////////////////////////////////////

#ifdef TRI_ENABLE_MRUBY
        ApplicationMR* _applicationMR;
#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief application V8
////////////////////////////////////////////////////////////////////////////////

        ApplicationV8* _applicationV8;

////////////////////////////////////////////////////////////////////////////////
/// @brief number of dispatcher threads for non-database worker
///
/// @CMDOPT{\--server.threads @CA{number}}
///
/// Specifies the @CA{number} of threads that are spawned to handle action
/// requests using Rest, JavaScript, or Ruby.
////////////////////////////////////////////////////////////////////////////////

        int _dispatcherThreads;

////////////////////////////////////////////////////////////////////////////////
/// @brief path to the database
///
/// @CMDOPT{\--database.directory @CA{directory}}
///
/// The directory containing the collections and data-files. Defaults
/// to @LIT{/var/lib/arango}.
///
/// @CMDOPT{@CA{directory}}
///
/// When using the command line version, you can simply supply the database
/// directory as argument.
///
/// @EXAMPLES
///
/// @verbinclude option-database-directory
////////////////////////////////////////////////////////////////////////////////

        string _databasePath;

////////////////////////////////////////////////////////////////////////////////
/// @brief remove on drop
///
/// @CMDOPT{\--database.remove-on-drop @CA{flag}}
///
/// If @LIT{true} and you drop a collection, then they directory and all
/// associated datafiles will be removed from disk. If @LIT{false}, then they
/// collection directory will be renamed to @LIT{deleted-...}, but remains on
/// hard disk. To restore such a dropped collection, you can rename the
/// directory back to @LIT{collection-...}, but you must also edit the file
/// @LIT{parameter.json} inside the directory.
///
/// The default is @LIT{true}.
////////////////////////////////////////////////////////////////////////////////

        bool _removeOnDrop;

////////////////////////////////////////////////////////////////////////////////
/// @brief remove on compaction
///
/// @CMDOPT{\--database.remove-on-compaction @CA{flag}}
///
/// Normally the garbage collection will removed compacted datafile. For debug
/// purposes you can use this option to keep the old datafiles. You should
/// never set it to @LIT{false} on a live system.
///
/// The default is @LIT{true}.
////////////////////////////////////////////////////////////////////////////////

        bool _removeOnCompacted;

////////////////////////////////////////////////////////////////////////////////
/// @brief default journal size
///
/// @CMDOPT{\--database.maximal-journal-size @CA{size}}
///
/// Maximal size of journal in bytes. Can be overwritten when creating a new
/// collection. Note that this also limits the maximal size of a single
/// document.
///
/// The default is @LIT{32MB}.
////////////////////////////////////////////////////////////////////////////////

        uint64_t _defaultMaximalSize;

////////////////////////////////////////////////////////////////////////////////
/// @brief default wait for sync behavior
///
/// @CMDOPT{\--database.wait-for-sync @CA{boolean}}
///
/// Default wait-for-sync value. Can be overwritten when creating a new
/// collection.
///
/// The default is @LIT{false}.
////////////////////////////////////////////////////////////////////////////////

        bool _defaultWaitForSync;

////////////////////////////////////////////////////////////////////////////////
/// @brief force sync shapes
///
/// @CMDOPT{\--database.force-sync-shapes @CA{boolean}}
///
/// Force syncing of shape data to disk when writing shape information. 
/// If turned off, syncing will still happen for shapes of collections that
/// have a waitForSync value of @LIT{true}. If turned on, syncing of shape data
/// will always happen, regards of the value of waitForSync.
///
/// The default is @LIT{true}.
////////////////////////////////////////////////////////////////////////////////

        bool _forceSyncShapes;

////////////////////////////////////////////////////////////////////////////////
/// @brief unit tests
///
/// @CMDOPT{\--javascript.unit-tests @CA{test-file}}
///
/// Runs one or more unit tests.
////////////////////////////////////////////////////////////////////////////////

        vector<string> _unitTests;

////////////////////////////////////////////////////////////////////////////////
/// @brief files to jslint
///
/// @CMDOPT{\--jslint @CA{test-file}}
///
/// Runs jslint on one or more files.
////////////////////////////////////////////////////////////////////////////////

        vector<string> _jslint;

////////////////////////////////////////////////////////////////////////////////
/// @brief run script file
///
/// @CMDOPT{\--javascript.script @CA{script-file}}
///
/// Runs the script file.
////////////////////////////////////////////////////////////////////////////////

        vector<string> _scriptFile;

////////////////////////////////////////////////////////////////////////////////
/// @brief parameters to script file
///
/// @CMDOPT{\--javascript.script-parameter @CA{script-parameter}}
///
/// Parameter to script.
////////////////////////////////////////////////////////////////////////////////

        vector<string> _scriptParameters;

////////////////////////////////////////////////////////////////////////////////
/// @brief server default language for sorting strings
///
/// @CMDOPT{\-\-default-language @CA{default-language}}
///
/// The default language ist used for sorting and comparing strings. 
/// The language value is a two-letter language code (ISO-639) or it is 
/// composed by a two-letter language code with and a two letter country code 
/// (ISO-3166). Valid languages are "de", "en", "en_US" or "en_UK".
///
/// The default default-language is set to be the system locale on that platform.
////////////////////////////////////////////////////////////////////////////////

        string _defaultLanguage;

////////////////////////////////////////////////////////////////////////////////
/// @brief vocbase
////////////////////////////////////////////////////////////////////////////////

        TRI_vocbase_t* _vocbase;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

#endif

// -----------------------------------------------------------------------------
// --SECTION--                                                       END-OF-FILE
// -----------------------------------------------------------------------------

// Local Variables:
// mode: outline-minor
// outline-regexp: "^\\(/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|/// @page\\|// --SECTION--\\|/// @\\}\\)"
// End:
