// Albumbrowse.h

#pragma once
#include "Stdafx.h"

using namespace System;
using namespace System::Collections::Generic;

namespace SpotiFire {
	
	ref class AlbumBrowse;
	ref class Album;
	ref class Artist;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Delegate for handling AlbumBrowse events. </summary>
	///
	/// <remarks>	Aleksander, 03.02.2013. </remarks>
	///
	/// <param name="sender">	The sender. </param>
	/// <param name="e">	 	The EventArgs to process. </param>
	///-------------------------------------------------------------------------------------------------
	public delegate void AlbumBrowseEventHandler(AlbumBrowse ^sender, EventArgs ^e);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Album browse. </summary>
	///
	/// <remarks>	Aleksander, 30.01.2013. </remarks>
	///-------------------------------------------------------------------------------------------------
	public ref class AlbumBrowse sealed : ISpotifyObject, ISpotifyAwaitable
	{
	private:
		IList<String ^> ^_copyrights;
		IList<Track ^> ^_tracks;

		List<Action ^> ^_continuations;
		bool _complete;

	internal:
		initonly Session ^_session;
		sp_albumbrowse *_ptr;

		AlbumBrowse(Session ^session, sp_albumbrowse *ptr);
		!AlbumBrowse(); // finalizer
		~AlbumBrowse(); // destructor

		

	public:

		///-------------------------------------------------------------------------------------------------
		/// <summary>	Gets the session. </summary>
		///
		/// <value>	The session. </value>
		///-------------------------------------------------------------------------------------------------
		virtual property Session ^Session { SpotiFire::Session ^get() sealed; }

		///-------------------------------------------------------------------------------------------------
		/// <summary>	Gets the error. </summary>
		///
		/// <value>	The error. </value>
		///-------------------------------------------------------------------------------------------------
		virtual property Error Error { SpotiFire::Error get() sealed; }

		///-------------------------------------------------------------------------------------------------
		/// <summary>	Gets the album. </summary>
		///
		/// <value>	The album. </value>
		///-------------------------------------------------------------------------------------------------
		virtual property Album ^Album { SpotiFire::Album ^get() sealed; }

		///-------------------------------------------------------------------------------------------------
		/// <summary>	Gets the artist. </summary>
		///
		/// <value>	The artist. </value>
		///-------------------------------------------------------------------------------------------------
		virtual property Artist ^Artist { SpotiFire::Artist ^get() sealed; }

		///-------------------------------------------------------------------------------------------------
		/// <summary>	Gets a value indicating whether this object is completed. </summary>
		///
		/// <value>	true if this object is completed, false if not. </value>
		///-------------------------------------------------------------------------------------------------
		virtual property bool IsLoaded { bool get() sealed; }

		///-------------------------------------------------------------------------------------------------
		/// <summary>	Gets the copyrights. </summary>
		///
		/// <value>	The copyrights. </value>
		///-------------------------------------------------------------------------------------------------
		virtual property IList<String ^> ^Copyrights { IList<String ^> ^get() sealed; }

		///-------------------------------------------------------------------------------------------------
		/// <summary>	Gets the tracks. </summary>
		///
		/// <value>	The tracks. </value>
		///-------------------------------------------------------------------------------------------------
		virtual property IList<Track ^> ^Tracks { IList<Track ^> ^get() sealed; }

		///-------------------------------------------------------------------------------------------------
		/// <summary>	Gets the review. </summary>
		///
		/// <value>	The review. </value>
		///-------------------------------------------------------------------------------------------------
		virtual property String ^Review { String ^get() sealed; }

	private:
		virtual property bool IsComplete { bool get() sealed = ISpotifyAwaitable::IsComplete::get; }
		virtual bool AddContinuation(Action ^continuationAction) sealed = ISpotifyAwaitable::AddContinuation;

	internal:
		static AlbumBrowse ^Create(SpotiFire::Session ^session, SpotiFire::Album ^album);

		// Events
		void complete();
	};
}
